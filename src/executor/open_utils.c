#include "open.h"
#include "libft.h"
#include "executor.h"
#include "executor_utils.h"
#include "readline.h"
#include "safe_utils.h"
#include "utils.h"
#include "builtins.h"
#include "signals.h"
#include <errno.h>

int	open_next_infile(t_redirection *file, int i, int *read_fd, int hdocs)
{
	int	fd;
	int	failed;

	failed = 0;
	fd = open_infile(file->path);
	if (fd == -1)
		failed = 1;
	if (i >= hdocs)
	{
		safe_close(read_fd);
		*read_fd = fd;
	}
	else
		safe_close(&fd);
	return (failed);
}

int	open_here_doc(int fds[2], t_redirection *here_doc)
{
	char	*line;

	listen_signals(HEREDOC, HEREDOC);
	line = readline(HERE_DOC_PREFIX);
	while (line && ft_strcmp(line, here_doc->delimiter))
	{
		if (ft_printff(fds[WRITE_FD], "%s\n", line) == -1)
		{
			free(line);
			close_pipe(fds);
			exit(EBADF);
		}
		free(line);
		line = readline(HERE_DOC_PREFIX);
	}
	free(line);
	close_pipe(fds);
	exit(EXIT_SUCCESS);
}
