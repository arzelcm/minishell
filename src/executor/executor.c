#include <errno.h>
#include "libft.h"
#include "executor.h"
#include "open.h"
#include "parser.h"
#include "parser_utils.h"
#include "utils.h"
#include "safe_utils.h"
#include "executor_utils.h"
#include "open_utils.h"

static void	execute_command(char **envp, t_pdata *pdata, t_token *token)
{
	pdata->fds[READ_FD] = \
		open_infiles(pdata->fds[READ_FD], token->infiles, token->here_docs);
	if (token->infiles && pdata->fds[READ_FD] == -1)
		exit(EXIT_FAILURE);
	pdata->fds[WRITE_FD] = open_outfiles(pdata->fds[WRITE_FD], token->outfiles);
	if (token->outfiles && pdata->fds[WRITE_FD] == -1)
	{
		safe_close(&pdata->fds[READ_FD]);
		exit(EXIT_FAILURE);
	}
	if (pdata->fds[READ_FD] != -1
		&& dup2(pdata->fds[READ_FD], STDIN_FILENO) == -1)
		handle_syserror(EBUSY);
	if (pdata->fds[WRITE_FD] != -1
		&& dup2(pdata->fds[WRITE_FD], STDOUT_FILENO) == -1)
		handle_syserror(EBUSY);
	close_pdata_fds(pdata);
	// TODO: Add builtins
	if (is_a_builtin(token->args[0]))
		exit(EXIT_SUCCESS);
	else if (!is_directory(token->args[0]))
		execute_by_path(token->args, envp);
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
	while (i < token->tokens.amount && cmd_token)
	{
		if (i < token->tokens.amount - 1 && pipe(pdata->pipe_fds) == -1)
			handle_syserror(ENOMEM);
		parse_fds(i, token->tokens.amount, pdata, cmd_token);
		pdata->pids[i] = fork();
		if (pdata->pids[i] == -1)
			handle_syserror(ENOMEM);
		else if (pdata->pids[i] == 0)
			execute_command(context->envp, pdata, cmd_token);
		close_pipe(pdata->fds);
		cmd_token = cmd_token->next;
		i++;
	}
}

void	execute(t_token *token, t_context *context)
{
	t_pdata	p_data;
	int		last_cmd_index;

	if (token->tokens.amount == 0)
		token->tokens.amount++;
	initialize_pdata(&p_data, token);
	last_cmd_index = token->tokens.amount - 1;
	if (token->type == CMD || token->type == PIPE)
		execute_pipe_token(&p_data, token, context);
	context->err_code = \
		wait_child_processes(p_data.pids[last_cmd_index], token->tokens.amount);
	free_pdata(&p_data);
}
