/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdata_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:04 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/14 20:15:06 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "open.h"
#include "executor_utils.h"
#include "safe_utils.h"
#include "utils.h"
#include <errno.h>
#include <signal.h>

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
		pdata->fds[READ_FD] = token->here_doc_fd;
	}
	if (token->outfiles || i == cmd_amount - 1)
		safe_close(&pdata->fds[WRITE_FD]);
	token->here_doc_fd = -1;
}

void	close_pdata_fds(t_pdata *pdata)
{
	close_pipe(pdata->fds);
	close_pipe(pdata->pipe_fds);
	close_pipe(pdata->std_fds);
	safe_close(&pdata->last_pipe);
}

void	save_backup_stdfds(t_pdata *p_data)
{
	if (isatty(STDIN_FILENO))
	{
		p_data->std_fds[READ_FD] = dup(STDIN_FILENO);
		if (p_data->std_fds[READ_FD] == -1)
			syserr(EBUSY);
	}
	p_data->std_fds[WRITE_FD] = dup(STDOUT_FILENO);
	if (p_data->std_fds[WRITE_FD] == -1)
		syserr(EBUSY);
}

// TODO: Dont initialize the pids here and do it in the needed function
// TODO: Safe initialization (if p_data is null, create one, or some approach like that, to prevent doing null checks)
void	initialize_pdata(t_pdata *p_data, t_token *token)
{
	ft_bzero(p_data, sizeof(t_pdata));
	p_data->last_pipe = -1;
	p_data->fds[READ_FD] = -1;
	p_data->fds[WRITE_FD] = -1;
	p_data->pipe_fds[READ_FD] = -1;
	p_data->pipe_fds[WRITE_FD] = -1;
	p_data->std_fds[READ_FD] = -1;
	p_data->std_fds[WRITE_FD] = -1;
	p_data->pids = safe_calloc((token->tokens.amount + 1) * sizeof(pid_t));
}
