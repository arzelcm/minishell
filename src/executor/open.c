#include "safe_utils.h"
#include "utils.h"
#include "libft.h"
#include "executor_utils.h"
#include "open_utils.h"
#include "open.h"
#include <signal.h>
#include <errno.h>

static void	wait_here_doc_process(int fds[2])
{
	int	status;

	if (waitpid(-1, &status, 0) == -1)
	{
		safe_close(&fds[READ_FD]);
		exit(ECHILD);
	}
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (status == EXIT_FAILURE)
			g_sigval = SIGINT;
		if (status == EBADF)
			handle_syserror(EBADF);
	}
}

static int	fork_here_doc(t_redirection *here_doc)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		handle_syserror(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		handle_syserror(EAGAIN);
	else if (pid == 0)
		open_here_doc(fds, here_doc);
	if (close(fds[WRITE_FD]) == -1)
	{
		safe_close(&fds[READ_FD]);
		kill(pid, SIGTERM);
		exit(EBADF);
	}
	wait_here_doc_process(fds);
	return (fds[READ_FD]);
}

int	open_here_docs(t_redirection *infiles, int here_docs_amount)
{
	int				i;
	int				fd;
	t_redirection	*file;

	i = 0;
	fd = -1;
	file = infiles;
	while (file && i < here_docs_amount)
	{
		if (file->mode == HERE_DOC)
		{
			fd = fork_here_doc(file);
			if (g_sigval == SIGINT)
				return (safe_close(&fd), -1);
			i++;
		}
		if (i != here_docs_amount)
			safe_close(&fd);
		file = file->next;
	}
	return (fd);
}

int	open_infiles(int read_fd, t_redirection *infiles, int here_docs_amount)
{
	int				i;
	int				failed;
	t_redirection	*file;

	i = 0;
	failed = 0;
	file = infiles;
	while (file)
	{
		if (file->mode != HERE_DOC)
			failed += open_next_infile(file, i, &read_fd, here_docs_amount);
		else
			i++;
		file = file->next;
	}
	if (failed)
		safe_close(&read_fd);
	return (read_fd);
}

int	open_outfiles(int write_fd, t_redirection *outfiles)
{
	int				fd;
	int				failed;
	t_redirection	*file;

	fd = write_fd;
	file = outfiles;
	failed = 0;
	while (file)
	{
		safe_close(&fd);
		fd = open_outfile(file->path, file->mode);
		if (fd == -1)
			failed++;
		file = file->next;
	}
	if (failed)
		safe_close(&fd);
	return (fd);
}
