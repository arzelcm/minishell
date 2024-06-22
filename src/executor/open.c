#include <sys/wait.h>
#include "libft.h"
#include "readline.h"
#include "context.h"
#include "signals.h"
#include "open.h"
#include "open_utils.h"
#include "safe_utils.h"
#include "executor_utils.h"
#include "tokenizer_redirections.h"
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

static int	open_next_infile(char *path, int i, int *read_fd, int hdcs)
{
	int	fd;
	int	failed;

	failed = 0;
	fd = open_infile(path);
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

static int	open_next_outfile(t_redirection *file, char *path, int *write_fd)
{
	safe_close(write_fd);
	*write_fd = open_outfile(path, file->mode);
	if (*write_fd == -1)
		return (1);
	return (0);
}

int	open_files(
	t_pdata *pdata, t_redirection *redirs, int hds_amnt, t_context *context)
{
	int				i;
	int				failed;
	char			*path;
	t_redirection	*file;

	i = 0;
	failed = 0;
	file = redirs;
	while (file)
	{
		path = expand_redirect(file, context);
		if (!path)
			return (close_pipe(pdata->fds), 0);
		if (file->mode == INPUT)
			failed = open_next_infile(path, i, &pdata->fds[READ_FD], hds_amnt);
		else if (file->mode == OUTPUT || file->mode == APPEND)
			failed = open_next_outfile(file, path, &pdata->fds[WRITE_FD]);
		else
			i++;
		if (failed)
			return (close_pipe(pdata->fds), 0);
		file = file->next;
	}
	return (1);
}
