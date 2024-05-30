#include "libft.h"
#include "builtins.h"
#include "token.h"

int	is_builtin(char *command)
{
	if (ft_strchr(command, '/'))
		return (0);
	return (ft_strcmp(command, PWD) == EQUAL_STRINGS
				|| ft_strcmp(command, ENV) == EQUAL_STRINGS
				|| ft_strcmp(command, ECHO) == EQUAL_STRINGS
				|| ft_strcmp(command, EXIT) == EQUAL_STRINGS
				|| ft_strcmp(command, EXPORT) == EQUAL_STRINGS);
}

int	exec_builtin(char *command, t_token *token, t_context *context)
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
	return (0);
}
