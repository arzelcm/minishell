#include "open.h"
#include "safe_utils.h"
#include "utils.h"
#include "execute_command_utils.h"
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

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

int	fork_here_doc(t_redirection *here_doc)
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
		kill(pid, SIGTERM);
		safe_close(&fds[READ_FD]);
		exit(EBADF);
	}
	wait_here_doc_process(fds);
	return (fds[READ_FD]);
}

int	open_infile(char *path)
{
	int		fd;
	char	*quoted_file;

	if (access(path, F_OK) == -1)
		return (handle_error(path, NOFILEDIR), -1);
	if (access(path, R_OK) == -1)
		return (handle_error(path, PERMDENIED), -1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		quoted_file = quote_str(path);
		handle_error("open: Error trying open file", quoted_file);
		free(quoted_file);
		return (-1);
	}
	return (fd);
}

int	open_outfile(char *path, int mode)
{
	int		fd;
	int		flags;
	char	*quoted_file;

	if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
		return (handle_error(path, PERMDENIED), -1);
	if (is_directory(path))
		return (handle_error(path, ISDIRECTORY_U), -1);
	flags = O_CREAT | O_WRONLY;
	if (mode == APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(path, flags, PERMBITS);
	if (fd < 0)
	{
		quoted_file = quote_str(path);
		handle_error("open: Error trying open file", quoted_file);
		free(quoted_file);
		return (-1);
	}
	return (fd);
}
