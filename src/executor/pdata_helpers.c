#include "libft.h"
#include "open.h"
#include "executor_utils.h"
#include "safe_utils.h"
#include "utils.h"
#include <errno.h>

void	free_pdata(t_pdata *p_data)
{
	free(p_data->pids);
	free(p_data->heredocs_fds);
}

void	close_pdata_fds(t_pdata *pdata)
{
	int	i;

	close_pipe(pdata->fds);
	close_pipe(pdata->pipe_fds);
	close_pipe(pdata->std_fds);
	safe_close(&pdata->last_pipe);
	i = 0;
	while (pdata->heredocs_fds[i])
		safe_close(&pdata->heredocs_fds[i++]);
}

void	save_backup_stdfds(t_pdata *p_data)
{
	p_data->std_fds[READ_FD] = dup(STDIN_FILENO);
	if (p_data->std_fds[READ_FD] == -1)
		handle_syserror(EBUSY);
	p_data->std_fds[WRITE_FD] = dup(STDIN_FILENO);
	if (p_data->std_fds[WRITE_FD] == -1)
		handle_syserror(EBUSY);
}

static void	initialize_heredocs(t_pdata *p_data, t_token *curr_token)
{
	int				i;
	int				here_docs;
	t_redirection	*infiles;

	i = 0;
	while (curr_token)
	{
		p_data->heredocs_fds[i] = -1;
		infiles = curr_token->infiles;
		here_docs = curr_token->here_docs;
		if (here_docs)
			p_data->heredocs_fds[i] = open_here_docs(infiles, here_docs);
		if (g_sigval == SIGINT)
			return (close_pdata_fds(p_data));
		curr_token = curr_token->next;
		i++;
	}
}

void	initialize_pdata(t_pdata *p_data, t_token *token, t_context *context)
{
	t_token	*curr_token;

	ft_bzero(p_data, sizeof(t_pdata));
	p_data->last_pipe = -1;
	p_data->fds[READ_FD] = -1;
	p_data->fds[WRITE_FD] = -1;
	p_data->pipe_fds[READ_FD] = -1;
	p_data->pipe_fds[WRITE_FD] = -1;
	p_data->std_fds[READ_FD] = -1;
	p_data->std_fds[WRITE_FD] = -1;
	p_data->pids = safe_calloc((token->tokens.amount + 1) * sizeof(pid_t));
	p_data->heredocs_fds = safe_calloc((token->tokens.amount +1) * sizeof(int));
	curr_token = token;
	if (token->tokens.amount > 1)
		curr_token = token->tokens.token;
	initialize_heredocs(p_data, curr_token);
	if (g_sigval == SIGINT)
		context->err_code = 1;
}
