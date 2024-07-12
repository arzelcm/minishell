/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:56 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/12 12:42:58 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "open.h"
#include "execute_command.h"
#include "utils.h"
#include "safe_utils.h"
#include "executor_utils.h"
#include "builtins.h"
#include "signals.h"
#include "token.h"
#include <signal.h>
#include <errno.h>

void	parse_fds(int i, int cmd_amount, t_pdata *pdata, t_token *token)
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

void	execute_pipe(t_pdata *pdata, t_token *token, t_context *context)
{
	t_token	*curr_token;
	int		i;
	int		last_idx;

	i = 0;
	last_idx = token->tokens.amount - 1;
	curr_token = token->tokens.token;
	while (i < token->tokens.amount && curr_token)
	{
		if (i < token->tokens.amount - 1 && pipe(pdata->pipe_fds) == -1)
			syserr(EMFILE);
		parse_fds(i, token->tokens.amount, pdata, curr_token);
		pdata->pids[i] = fork();
		if (pdata->pids[i] == -1)
			syserr(EAGAIN);
		else if (pdata->pids[i] == 0)
		{
			if (curr_token->type == CMD)
				execute_command(pdata, curr_token, context);
			else if (curr_token->type == SUBSHELL)
			{
				execute_subshell(pdata, token, context);
				exit(context->err_code);
			}
		}
		close_pipe(pdata->fds);
		curr_token = curr_token->next;
		i++;
	}
	context->err_code = \
		wait_child_processes(pdata->pids[last_idx], token->tokens.amount);
}

void	execute_cmd(t_pdata *pdata, t_token *token, t_context *context)
{
	pdata->pids[0] = fork();
	if (pdata->pids[0] == -1)
		syserr(EAGAIN);
	else if (pdata->pids[0] == 0)
		execute_command(pdata, token, context);
	context->err_code = wait_child_processes(pdata->pids[0], 1);
}

void	execute_list(t_pdata *pdata, t_token *token, t_context *context)
{
	t_token	*curr_token;

	curr_token = token->tokens.token;
	expand_args(curr_token, context);
	execute_token(pdata, curr_token, context);
	if ((token->dependency == AND && context->err_code != 0)
		|| (token->dependency == OR && context->err_code == 0))
		return ;
	curr_token = curr_token->next;
	expand_args(curr_token, context);
	execute_token(pdata, curr_token, context);
}

void	execute_subshell(t_pdata *pdata, t_token *token, t_context *context)
{
	t_token	*curr_token;

	save_backup_stdfds(pdata);
	if (!open_files(pdata, token->redirections, token->here_docs, context))
	{
		context->err_code = EXIT_FAILURE;
		return (close_pdata_fds(pdata));
	}
	redirect_fds(pdata->fds[READ_FD], pdata->fds[WRITE_FD]);
	close_pdata_fds(pdata);
	curr_token = token->tokens.token;
	pdata->pids[0] = fork();
	if (pdata->pids[0] == 0)
	{
		expand_args(curr_token, context);
		execute_token(pdata, curr_token, context);
		exit(context->err_code);
	}
	context->err_code = wait_child_processes(pdata->pids[0], 1);
	redirect_fds(pdata->std_fds[READ_FD], pdata->std_fds[WRITE_FD]);
	close_pdata_fds(pdata);
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
	expand_args(token, context);
	execute_token(&p_data, token, context);
	free_pdata(&p_data);
}
