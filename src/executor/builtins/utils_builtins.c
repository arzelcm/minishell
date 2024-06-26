#include "libft.h"
#include "builtins.h"
#include "signals.h"
#include "open.h"
#include "executor_utils.h"

int	is_builtin(char *command)
{
	if (ft_strchr(command, '/'))
		return (0);
	return (ft_strcmp(command, PWD) == EQUAL_STRINGS
		|| ft_strcmp(command, ENV) == EQUAL_STRINGS
		|| ft_strcmp(command, ECHO) == EQUAL_STRINGS
		|| ft_strcmp(command, EXIT) == EQUAL_STRINGS
		|| ft_strcmp(command, EXPORT) == EQUAL_STRINGS
		|| ft_strcmp(command, UNSET) == EQUAL_STRINGS
		|| ft_strcmp(command, CD) == EQUAL_STRINGS);
}

int	execute_builtin(char *command, t_token *token, t_context *context)
{
	if (ft_strchr(command, '/'))
		return (0);
	else if (ft_strcmp(command, PWD) == EQUAL_STRINGS)
		return (ft_pwd(token->argc, token->args, context));
	else if (ft_strcmp(command, ENV) == EQUAL_STRINGS)
		return (ft_env(token->argc, token->args, context));
	else if (ft_strcmp(command, ECHO) == EQUAL_STRINGS)
		return (ft_echo(token->argc, token->args, context));
	else if (ft_strcmp(command, EXIT) == EQUAL_STRINGS)
		return (ft_exit(token->argc, token->args, context));
	else if (ft_strcmp(command, EXPORT) == EQUAL_STRINGS)
		return (ft_export(token->argc, token->args, context));
	else if (ft_strcmp(command, UNSET) == EQUAL_STRINGS)
		return (ft_unset(token->argc, token->args, context));
	else if (ft_strcmp(command, CD) == EQUAL_STRINGS)
		return (ft_cd(token->argc, token->args, context));
	return (0);
}

void	execute_cmd_builtin(t_pdata *pdata, t_token *token, t_context *context)
{
	listen_signals(SUBPROCESS, SUBPROCESS);
	save_backup_stdfds(pdata);
	pdata->fds[READ_FD] = \
		open_infiles(pdata->fds[READ_FD], token->infiles, token->here_docs);
	if (token->infiles && pdata->fds[READ_FD] == -1)
	{
		context->err_code = 1;
		return (close_pdata_fds(pdata));
	}
	pdata->fds[WRITE_FD] = open_outfiles(pdata->fds[WRITE_FD], token->outfiles);
	if (token->outfiles && pdata->fds[WRITE_FD] == -1)
	{
		context->err_code = 1;
		return (close_pdata_fds(pdata));
	}
	redirect_fds(pdata->fds[READ_FD], pdata->fds[WRITE_FD]);
	context->err_code = execute_builtin(token->args[0], token, context);
	redirect_fds(pdata->std_fds[READ_FD], pdata->std_fds[WRITE_FD]);
	close_pdata_fds(pdata);
}
