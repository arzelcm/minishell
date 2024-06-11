#include <errno.h>
#include "libft.h"
#include "pdata_helpers.h"
#include "open.h"
#include "parser.h"
#include "parser_utils.h"
#include "utils.h"
#include "safe_utils.h"
#include "executor_utils.h"
#include "open_utils.h"
#include "builtins.h"
#include "signals.h"

static void	
	exec_command(int doExit, t_pdata *pdata, t_token *token, t_context *context)
{
	listen_signals(SUBPROCESS, SUBPROCESS);
	pdata->fds[READ_FD] = \
		open_infiles(pdata->fds[READ_FD], token->infiles, token->here_docs);
	if (token->infiles && pdata->fds[READ_FD] == -1)
	{
		close_pdata_fds(pdata);
		close_pipe(pdata->std_fds);
		if (doExit == 0)
			return ;
		exit(EXIT_FAILURE);
	}
	pdata->fds[WRITE_FD] = open_outfiles(pdata->fds[WRITE_FD], token->outfiles);
	if (token->outfiles && pdata->fds[WRITE_FD] == -1)
	{
		close_pdata_fds(pdata);
		close_pipe(pdata->std_fds);
		if (doExit == 0)
			return ;
		exit(EXIT_FAILURE);
	}
	if (pdata->fds[READ_FD] != -1
		&& dup2(pdata->fds[READ_FD], STDIN_FILENO) == -1)
		handle_syserror(EBUSY);
	if (pdata->fds[WRITE_FD] != -1
		&& dup2(pdata->fds[WRITE_FD], STDOUT_FILENO) == -1)
		handle_syserror(EBUSY);
	close_pdata_fds(pdata);
	if (is_builtin(token->args[0]))
	{
		context->err_code = exec_builtin(token->args[0], token, context);
		if (pdata->std_fds[READ_FD] != -1
			&& dup2(pdata->std_fds[READ_FD], STDIN_FILENO) == -1)
			handle_syserror(EBUSY);
		if (pdata->std_fds[WRITE_FD] != -1
			&& dup2(pdata->std_fds[WRITE_FD], STDOUT_FILENO) == -1)
			handle_syserror(EBUSY);
		close_pipe(pdata->std_fds);
		if (doExit == 0)
			return ;
		exit(context->err_code);
	}
	close_pipe(pdata->std_fds);
	if (!is_directory(token->args[0]))
		execute_by_path(token->args, context->global_env.envp);
	handle_error(token->args[0], ISDIRECTORY);
	exit(PERM_ERR);
}

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

static void	\
	execute_pipe_token(t_pdata *pdata, t_token *token, t_context *context)
{
	t_token	*cmd_token;
	int		i;

	i = 0;
	cmd_token = token;
	if (token->type != CMD)
		cmd_token = token->tokens.token;
	close_pipe(pdata->std_fds);
	while (i < token->tokens.amount && cmd_token)
	{
		if (i < token->tokens.amount - 1 && pipe(pdata->pipe_fds) == -1)
			handle_syserror(ENOMEM);
		parse_fds(i, token->tokens.amount, pdata, cmd_token);
		pdata->pids[i] = fork();
		if (pdata->pids[i] == -1)
			handle_syserror(EAGAIN);
		else if (pdata->pids[i] == 0)
			exec_command(1, pdata, cmd_token, context);
		close_pipe(pdata->fds);
		cmd_token = cmd_token->next;
		i++;
	}
}

void	execute(t_token *token, t_context *context)
{
	t_pdata	p_data;
	int		last_cmd_index;

	listen_signals(MAIN, EXECUTOR);
	if (!token)
		return ;
	if (token->tokens.amount == 0)
		token->tokens.amount++;
	initialize_pdata(&p_data, token);
	if (g_sigval == SIGINT)
	{
		g_sigval = 0;
		context->err_code = 1;
		free_pdata(&p_data);
		return ;
	}
	config_echoctl_terminal(ON);
	last_cmd_index = token->tokens.amount - 1;
	if (token->type == CMD && is_builtin(token->args[0]))
		exec_command(0, &p_data, token, context);
	else if (token->type == CMD || token->type == PIPE)
		execute_pipe_token(&p_data, token, context);
	if (!(token->type == CMD && is_builtin(token->args[0])))
		context->err_code = wait_child_processes(
				p_data.pids[last_cmd_index], token->tokens.amount);
	free_pdata(&p_data);
}
