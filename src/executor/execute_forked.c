/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_forked.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:53:54 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/07/15 18:16:46 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pdata_helpers.h"
#include "here_docs_utils.h"
#include "execute_command.h"
#include "executor.h"
#include "executor_utils.h"

void	execute_forked_subshell(
	t_token *curr_token, t_token *token, t_pdata *pdata, t_context *context)
{
	expand_args(curr_token, context);
	execute_token(NULL, curr_token, context);
	close_pdata_fds(pdata);
	close_here_docs(token);
	exit(context->err_code);
}

void	execute_forked_pipe(
	pid_t *pids, t_pdata *pdata, t_token *token, t_context *context)
{
	free(pids);
	if (token->type == CMD)
		execute_command(pdata, token, context);
	else if (token->type == SUBSHELL)
	{
		execute_subshell(pdata, token, context);
		close_here_docs(token);
		exit(context->err_code);
	}
}

void	clean_pipe(pid_t *pids, t_token *token, t_context *context)
{
	int	last_cmd_idx;

	last_cmd_idx = token->tokens.amount - 1;
	context->err_code = wait_child_processes(pids[last_cmd_idx], token->tokens.amount);
	free(pids);
}
