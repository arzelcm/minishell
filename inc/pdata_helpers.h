/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdata_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:34 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/15 15:59:56 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PDATA_HELPERS_H
# define PDATA_HELPERS_H

# include "token.h"
# include "context.h"

typedef struct s_pdata
{
	int		std_fds[2];
	int		fds[2];
	int		pipe_fds[2];
	int		last_pipe;
}	t_pdata;

void	parse_fds(int i, int cmd_amount, t_pdata *pdata, t_token *token);

void	close_pdata_fds(t_pdata *pdata);

void	save_backup_stdfds(t_pdata *p_data);

void	initialize_pdata(t_pdata *p_data);

#endif
