/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdata_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:34 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/12 17:27:27 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PDATA_HELPERS_H
# define PDATA_HELPERS_H

# include "token.h"
# include "context.h"
# include <stdlib.h>

typedef struct s_pdata
{
	pid_t	*pids;
	int		std_fds[2];
	int		fds[2];
	int		pipe_fds[2];
	int		last_pipe;
}	t_pdata;

void	parse_fds(int i, int cmd_amount, t_pdata *pdata, t_token *token);

void	close_pdata_fds(t_pdata *pdata);

void	save_backup_stdfds(t_pdata *p_data);

void	initialize_pdata(t_pdata *p_data, t_token *token);

#endif
