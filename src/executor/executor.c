#include <errno.h>
#include "libft.h"
#include "executor.h"
#include "open.h"
#include "parser.h"
#include "utils.h"
#include "safe_utils.h"
#include "executor_utils.h"

static void	execute_command(int fds[2], char **envp, t_token *token)
{
	fds[READ_FD] = open_infiles(fds[READ_FD], token->infiles, token->here_docs);
	fds[WRITE_FD] = open_outfiles(fds[WRITE_FD], token->outfiles);
	if (fds[READ_FD] != -1 && dup2(fds[READ_FD], STDIN_FILENO) == -1)
		handle_syserror(EBUSY);
	if (fds[WRITE_FD] != -1 && dup2(fds[WRITE_FD], STDOUT_FILENO) == -1)
		handle_syserror(EBUSY);
	close_pipe(fds);
	// TODO: Add builtins
	if (is_a_builtin(token->args[0]))
		exit(EXIT_SUCCESS);
	else
		execute_by_path(token->args, envp);
	exit(EXIT_FAILURE);
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
		execute_command(fds, context->envp, token);
	if (token->here_docs)
		safe_close(&fds[READ_FD]);
	waitpid(pid, &context->err_code, 0);
}

void	execute(t_token *token, t_context *context)
{
	if (token->type == CMD)
		execute_cmd_token(token, context);
}