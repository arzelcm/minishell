#include <sys/wait.h>
#include "libft.h"
#include "readline.h"
#include "context.h"
#include "signals.h"
#include "open.h"
#include "open_utils.h"
#include "safe_utils.h"
#include "executor_utils.h"
#include <signal.h>
#include <errno.h>

int	open_here_doc(int fds[2], t_redirection *here_doc)
{
	char	*line;

	listen_signals(HEREDOC, HEREDOC);
	if (isatty(STDIN_FILENO))
		line = readline(HERE_DOC_PREFIX);
	else
		line = get_next_line(STDIN_FILENO, 0);
	while (line && ft_strcmp(line, here_doc->delimiter))
	{
		if (ft_printff(fds[WRITE_FD], "%s\n", line) == -1)
		{
			free(line);
			close_pipe(fds);
			exit(EBADF);
		}
		free(line);
		if (isatty(STDIN_FILENO))
			line = readline(HERE_DOC_PREFIX);
		else
			line = get_next_line(STDIN_FILENO, 0);
	}
	free(line);
	close_pipe(fds);
	exit(EXIT_SUCCESS);
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
			{
				safe_close(&fd);
				return (-1);
			}
			i++;
		}
		if (i != here_docs_amount)
			safe_close(&fd);
		file = file->next;
	}
	return (fd);
}

static int	open_next_infile(t_redirection *file, int i, int *read_fd, int hdcs)
{
	int	fd;
	int	failed;

	failed = 0;
	fd = open_infile(file->path);
	if (fd == -1)
		failed = 1;
	if (i >= hdcs)
	{
		safe_close(read_fd);
		*read_fd = fd;
	}
	else
		safe_close(&fd);
	return (failed);
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
