#include <errno.h>
#include "libft.h"
#include "executor.h"
#include "open.h"
#include "parser.h"
#include "parser_utils.h"
#include "utils.h"
#include "safe_utils.h"
#include "executor_utils.h"

static void	execute_command(int fds[2], char **envp, t_token *token, t_context *context)
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
	if (is_a_builtin(token->args[0], token, context))
		exit(EXIT_SUCCESS);
	else if (!is_directory(token->args[0]))
		execute_by_path(token->args, envp);
	handle_error(token->args[0], ISDIRECTORY);
	exit(PERM_ERR);
}

static void	execute_cmd_token(t_token *token, t_context *context)
{
	int		fds[2];
	pid_t	pid;

	fds[READ_FD] = -1;
	fds[WRITE_FD] = -1;
	if (token->here_docs)
		fds[READ_FD] = open_here_docs(token->infiles, token->here_docs);
	pid = fork();
	if (pid < 0)
		handle_syserror(ENOMEM);
	else if (pid == 0)
		execute_command(fds, context->env.global, token, context);
	if (token->here_docs)
		safe_close(&fds[READ_FD]);
	context->err_code = wait_child_processes(pid, 1);
}

void	execute(t_token *token, t_context *context)
{
	if (!token)
		return ;
	else if (token->type == CMD)
		execute_cmd_token(token, context);
}
