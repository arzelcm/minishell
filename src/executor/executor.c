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

static void	execute_command(int fds[2], char **envp, t_token *token)
{
	fds[READ_FD] = open_infiles(fds[READ_FD], token->infiles, token->here_docs);
	if (token->infiles && fds[READ_FD] == -1)
		exit(EXIT_FAILURE);
	fds[WRITE_FD] = open_outfiles(fds[WRITE_FD], token->outfiles);
	if (token->outfiles && fds[WRITE_FD] == -1)
	{
		safe_close(&fds[READ_FD]);
		exit(EXIT_FAILURE);
	}
	if (fds[READ_FD] != -1 && dup2(fds[READ_FD], STDIN_FILENO) == -1)
		handle_syserror(EBUSY);
	if (fds[WRITE_FD] != -1 && dup2(fds[WRITE_FD], STDOUT_FILENO) == -1)
		handle_syserror(EBUSY);
	close_pipe(fds);
	// TODO: Add builtins
	if (is_a_builtin(token->args[0]))
		exit(EXIT_SUCCESS);
	else if (!is_directory(token->args[0]))
		execute_by_path(token->args, envp);
	handle_error(token->args[0], ISDIRECTORY);
	exit(PERM_ERR);
}

static void	\
	execute_cmd_token(int i, t_pdata *pdata, t_token *token, t_context *context)
{
	pdata->fds[READ_FD] = pdata->hd_fds[i];
	pdata->pids[i] = fork();
	if (pdata->pids[i] < 0)
		handle_syserror(ENOMEM);
	else if (pdata->pids[i] == 0)
		execute_command(pdata->fds, context->envp, token);
	if (token->here_docs)
		safe_close(&pdata->fds[READ_FD]);
}

void	execute(t_token *token, t_context *context)
{
	t_pdata	p_data;
	int		last_cmd_index;

	initialize_pdata(&p_data, token);
	last_cmd_index = token->tokens.amount - 1;
	if (token->type == CMD)
		execute_cmd_token(last_cmd_index, &p_data, token, context);
	context->err_code = \
		wait_child_processes(p_data.pids[last_cmd_index], token->tokens.amount);
	free_pdata(&p_data);
}
