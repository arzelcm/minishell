#include "libft.h"
#include "open.h"
#include "execute_command.h"
#include "utils.h"
#include "safe_utils.h"
#include "executor_utils.h"
#include "builtins.h"
#include "signals.h"
#include <signal.h>
#include <errno.h>

static void	parse_fds(int i, int cmd_amount, t_pdata *pdata, t_token *token)
{
	int	tmp;

	tmp = pdata->last_pipe;
	pdata->last_pipe = pdata->pipe_fds[READ_FD];
	pdata->fds[READ_FD] = tmp;
	pdata->fds[WRITE_FD] = pdata->pipe_fds[WRITE_FD];
	pdata->pipe_fds[READ_FD] = -1;
	pdata->pipe_fds[WRITE_FD] = -1;
	if (token->infiles)
	{
		safe_close(&pdata->fds[READ_FD]);
		pdata->fds[READ_FD] = pdata->heredocs_fds[i];
	}
	if (token->outfiles || i == cmd_amount - 1)
		safe_close(&pdata->fds[WRITE_FD]);
	pdata->heredocs_fds[i] = -1;
}

static void	execute_pipe(t_pdata *pdata, t_token *token, t_context *context)
{
	t_token	*cmd_token;
	int		i;
	int		last_cmd_idx;

	i = 0;
	cmd_token = token;
	last_cmd_idx = token->tokens.amount - 1;
	if (token->type != CMD)
		cmd_token = token->tokens.token;
	while (i < token->tokens.amount && cmd_token)
	{
		if (i < token->tokens.amount - 1 && pipe(pdata->pipe_fds) == -1)
			handle_syserror(EMFILE);
		parse_fds(i, token->tokens.amount, pdata, cmd_token);
		pdata->pids[i] = fork();
		if (pdata->pids[i] == -1)
			handle_syserror(EAGAIN);
		else if (pdata->pids[i] == 0)
			execute_command(pdata, cmd_token, context);
		close_pipe(pdata->fds);
		cmd_token = cmd_token->next;
		i++;
	}
	context->err_code = \
		wait_child_processes(pdata->pids[last_cmd_idx], token->tokens.amount);
}

void	execute(t_token *token, t_context *context)
{
	t_pdata	p_data;

	listen_signals(MAIN, EXECUTOR);
	if (!token)
		return ;
	if (token->tokens.amount == 0)
		token->tokens.amount++;
	initialize_pdata(&p_data, token, context);
	if (g_sigval == SIGINT)
	{
		g_sigval = 0;
		return (free_pdata(&p_data));
	}
	config_echoctl_terminal(ON);
	// TODO: Expand args void	expand_tok_args(t_token *token, t_context *context);
	if (token->type == CMD && token->argc && is_builtin(token->args[0]))
		execute_cmd_builtin(&p_data, token, context);
	else if (token->type == CMD || token->type == PIPE)
		execute_pipe(&p_data, token, context);
	free_pdata(&p_data);
}
