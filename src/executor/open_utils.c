#include "open.h"
#include "libft.h"
#include "executor.h"
#include "executor_utils.h"
#include "readline.h"
#include "safe_utils.h"
#include "utils.h"
#include <errno.h>

void	free_pdata(t_pdata *p_data)
{
	free(p_data->pids);
	free(p_data->hd_fds);
}

void	close_pdata_fds(t_pdata *pdata)
{
	int	i;

	close_pipe(pdata->fds);
	close_pipe(pdata->pipe_fds);
	safe_close(&pdata->last_pipe);
	i = 0;
	while (pdata->hd_fds[i])
		safe_close(&pdata->hd_fds[i++]);
}

void	initialize_pdata(t_pdata *p_data, t_token *token)
{
	t_token	*curr_token;
	int		i;

	ft_bzero(p_data, sizeof(t_pdata));
	p_data->last_pipe = -1;
	p_data->fds[READ_FD] = -1;
	p_data->fds[WRITE_FD] = -1;
	p_data->pipe_fds[READ_FD] = -1;
	p_data->pipe_fds[WRITE_FD] = -1;
	p_data->pids = safe_calloc((token->tokens.amount + 1) * sizeof(pid_t));
	p_data->hd_fds = safe_calloc((token->tokens.amount + 1) * sizeof(int));
	curr_token = token;
	if (token->tokens.amount > 1)
		curr_token = token->tokens.token;
	i = 0;
	while (curr_token)
	{
		p_data->hd_fds[i] = -1;
		if (curr_token->here_docs)
			p_data->hd_fds[i] = \
				open_here_docs(curr_token->infiles, curr_token->here_docs);
		curr_token = curr_token->next;
		i++;
	}
}

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

int	open_here_doc(t_redirection *here_doc)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		handle_syserror(EXIT_FAILURE);
	line = readline(HERE_DOC_PREFIX);
	while (line && ft_strcmp(line, here_doc->delimiter))
	{
		if (ft_printff(fds[WRITE_FD], "%s\n", line) == -1)
		{
			free(line);
			safe_close(&fds[READ_FD]);
			safe_close(&fds[WRITE_FD]);
			exit(ENOENT);
		}
		free(line);
		line = readline(HERE_DOC_PREFIX);
	}
	free(line);
	safe_close(&fds[WRITE_FD]);
	return (fds[READ_FD]);
}
