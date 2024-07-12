/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:46 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/12 17:38:02 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_pdata	new_pdata;

	ft_bzero(&new_pdata, sizeof(t_pdata*));
	if (!pdata)
	{
		initialize_pdata(&new_pdata, token);
		pdata = &new_pdata;
	}
	listen_signals(SUBPROCESS, SUBPROCESS);
	save_backup_stdfds(pdata);
	if (!open_files(pdata, token->redirections, token->here_docs, context))
	{
		context->err_code = EXIT_FAILURE;
		return (close_pdata_fds(pdata));
	}
	redirect_fds(pdata->fds[READ_FD], pdata->fds[WRITE_FD]);
	context->err_code = execute_builtin(token->args[0], token, context);
	redirect_fds(pdata->std_fds[READ_FD], pdata->std_fds[WRITE_FD]);
	close_pdata_fds(pdata);
	if (new_pdata.pids)
		free(pdata->pids);
}

int	check_invalid_chars(char *identifier)
{
	int	i;

	i = 0;
	while (identifier[i] != '\0' && identifier[i] != '=')
	{
		if ((!ft_isalnum(identifier[i])
				&& identifier[i] != '_' && identifier[i] != '+'
				&& !ft_stroccurrences("ºª", identifier[i]))
			|| (identifier[i] == '+' && identifier[i + 1] != '='))
			return (0);
		i++;
	}
	return (1);
}
