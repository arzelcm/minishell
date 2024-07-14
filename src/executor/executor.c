/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:56 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/14 20:48:09 by cfidalgo         ###   ########.fr       */
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
#include "here_docs_utils.h"
#include <signal.h>
#include <errno.h>

void	execute_subshell(t_pdata *pdata, t_token *token, t_context *context)
{
	t_token	*curr_token;
	t_pdata	new_pdata;
	pid_t	pid;

	ft_bzero(&new_pdata, sizeof(t_pdata*));
	if (!pdata)
	{
		initialize_pdata(&new_pdata, token);
		pdata = &new_pdata;
	}
	save_backup_stdfds(pdata);
	if (!open_files(pdata, token->redirections, token->here_docs, context))
	{
		context->err_code = EXIT_FAILURE;
		return (close_pdata_fds(pdata));
	}
	redirect_fds(pdata->fds[READ_FD], pdata->fds[WRITE_FD]);
	close_pipe(pdata->fds);
	curr_token = token->tokens.token;
	pid = fork();
	if (pid == 0)
	{
		expand_args(curr_token, context);
		execute_token(NULL, curr_token, context);
		close_pdata_fds(pdata);
		close_here_docs(token);
		exit(context->err_code);
	}
	context->err_code = wait_child_processes(pid, 1);
	redirect_fds(pdata->std_fds[READ_FD], pdata->std_fds[WRITE_FD]);
	close_pdata_fds(pdata);
	if (new_pdata.pids)
		free(pdata->pids);
}

void	execute_pipe_temp(t_pdata *pdata, t_token *token, t_context *context)
{
	if (token->type == CMD)
		execute_command(pdata, token, context);
	else if (token->type == SUBSHELL)
	{
		execute_subshell(pdata, token, context);
		close_here_docs(token);
		exit(context->err_code);
	}
}

void	execute_pipe(t_token *token, t_context *context)
{
	t_token	*curr_token;
	t_pdata	pdata;
	int		i;
	int		last_idx;

	i = 0;
	last_idx = token->tokens.amount - 1;
	curr_token = token->tokens.token;
	initialize_pdata(&pdata, token);
	while (i < token->tokens.amount && curr_token)
	{
		if (i < token->tokens.amount - 1 && pipe(pdata.pipe_fds) == -1)
			syserr(EMFILE);
		parse_fds(i, token->tokens.amount, &pdata, curr_token);
		pdata.pids[i] = fork();
		if (pdata.pids[i] == -1)
			syserr(EAGAIN);
		else if (pdata.pids[i] == 0)
			execute_pipe_temp(&pdata, curr_token, context);
		close_pipe(pdata.fds);
		curr_token = curr_token->next;
		i++;
	}
	context->err_code = \
		wait_child_processes(pdata.pids[last_idx], token->tokens.amount);
	free(pdata.pids);
}

void	execute_cmd(t_token *token, t_context *context)
{
	t_pdata	pdata;

	initialize_pdata(&pdata, token);
	parse_fds(0, 1, &pdata, token);
	pdata.pids[0] = fork();
	if (pdata.pids[0] == -1)
		syserr(EAGAIN);
	else if (pdata.pids[0] == 0)
		execute_command(&pdata, token, context);
	close_pipe(pdata.fds);
	context->err_code = wait_child_processes(pdata.pids[0], 1);
	free(pdata.pids);
}

void	execute_list(t_token *token, t_context *context)
{
	t_token	*curr_token;

	curr_token = token->tokens.token;
	expand_args(curr_token, context);
	execute_token(NULL, curr_token, context);
	if ((token->dependency == AND && context->err_code != 0)
		|| (token->dependency == OR && context->err_code == 0))
		return ;
	curr_token = curr_token->next;
	expand_args(curr_token, context);
	execute_token(NULL, curr_token, context);
}

void	execute(t_token *token, t_context *context)
{
	listen_signals(MAIN, EXECUTOR);
	if (!token)
		return ;
	initialize_heredocs(token);
	if (g_sigval == SIGINT)
	{
		g_sigval = 0;
		context->err_code = 1;
		return ;
	}
	config_echoctl_terminal(ON);
	expand_args(token, context);
	execute_token(NULL, token, context);
	close_here_docs(token);
}
