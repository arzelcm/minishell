/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:03 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/10 20:03:30 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "pdata_helpers.h"
# include <stdlib.h>

int		wait_child_processes(pid_t last_pid, int cmds_amount);

void	close_pipe(int fds[2]);

void	redirect_fds(int read_fd, int write_fd);

void	clean_exit(t_pdata *pdata);

void	execute_token(t_pdata *p_data, t_token *token, t_context *context);

#endif
