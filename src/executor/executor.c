/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:56 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/16 12:29:15 by arcanava         ###   ########.fr       */
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
#include "execute_forked.h"
#include <signal.h>
#include <errno.h>

void	execute_subshell(t_pdata *pdata, t_token *token, t_context *context)
{
	t_token	*curr_token;
	t_pdata	new_pdata;
	pid_t	pid;

	ft_bzero(&new_pdata, sizeof(t_pdata *));
	set_pdata(&new_pdata, &pdata);
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
		execute_forked_subshell(curr_token, token, pdata, context);
	context->err_code = wait_child_processes(pid, 1);
	redirect_fds(pdata->std_fds[READ_FD], pdata->std_fds[WRITE_FD]);
	close_pdata_fds(pdata);
}

void	execute_pipe(t_token *token, t_context *context)
{
	t_token	*curr_token;
	t_pdata	pdata;
	pid_t	*pids;
	int		i;

	i = 0;
	curr_token = token->tokens.token;
	pids = safe_calloc((token->tokens.amount + 1) * sizeof(pid_t));
	initialize_pdata(&pdata);
	while (i < token->tokens.amount && curr_token)
	{
		if (i < token->tokens.amount - 1 && pipe(pdata.pipe_fds) == -1)
			syserr(EMFILE);
		parse_fds(i, token->tokens.amount, &pdata, curr_token);
		pids[i] = fork();
		if (pids[i] == -1)
			syserr(EAGAIN);
		else if (pids[i] == 0)
			execute_forked_pipe(pids, &pdata, curr_token, context);
		close_pipe(pdata.fds);
		curr_token = curr_token->next;
		i++;
	}
	clean_pipe(pids, token, context);
}

void	execute_cmd(t_token *token, t_context *context)
{
	t_pdata	pdata;
	pid_t	pid;

	initialize_pdata(&pdata);
	parse_fds(0, 1, &pdata, token);
	pid = fork();
	if (pid == -1)
		syserr(EAGAIN);
	else if (pid == 0)
		execute_command(&pdata, token, context);
	close_pipe(pdata.fds);
	context->err_code = wait_child_processes(pid, 1);
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
