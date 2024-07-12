/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:54 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/12 19:54:15 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "open.h"
#include "safe_utils.h"
#include "utils.h"
#include "pdata_helpers.h"
#include "executor.h"
#include "builtins.h"
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

int	wait_child_processes(pid_t last_pid, int cmds_amount)
{
	pid_t	pid;
	int		tmp;
	int		status;

	status = 1;
	while (cmds_amount-- > 0)
	{
		pid = waitpid(-1, &tmp, 0);
		if (pid < 0)
			syserr(ECHILD);
		if (pid == last_pid && WIFEXITED(tmp))
			status = WEXITSTATUS(tmp);
		else if (pid == last_pid && WIFSIGNALED(tmp))
		{
			status = WTERMSIG(tmp);
			if (status == SIGINT)
				status = SIGERR_SIGINT;
			else if (status == SIGQUIT)
				status = SIGERR_SIGQUIT;
			if (status == SIGERR_SIGQUIT)
				ft_printff(STDERR_FILENO, "Quit: 3");
			ft_printff(STDERR_FILENO, "\n");
		}
	}
	return (status);
}

void	close_pipe(int fds[2])
{
	safe_close(&fds[READ_FD]);
	safe_close(&fds[WRITE_FD]);
}

void	redirect_fds(int read_fd, int write_fd)
{
	if (read_fd != -1 && dup2(read_fd, STDIN_FILENO) == -1)
		syserr(EBUSY);
	if (write_fd != -1 && dup2(write_fd, STDOUT_FILENO) == -1)
		syserr(EBUSY);
}

void	clean_exit(t_pdata *pdata)
{
	//close_here_docs();
	close_pdata_fds(pdata);
	exit(EXIT_FAILURE);
}

void
	execute_token(t_pdata *p_data, t_token *token, t_context *context)
{
	if (token->type == CMD && token->argc && is_builtin(token->args[0]))
		execute_cmd_builtin(p_data, token, context);
	else if (token->type == CMD)
		execute_cmd(token, context);
	else if (token->type == PIPE)
		execute_pipe(token, context);
	else if (token->type == LIST)
		execute_list(token, context);
	else if (token->type == SUBSHELL)
		execute_subshell(p_data, token, context);
}
