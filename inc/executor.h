/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:06 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/11 18:47:24 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "context.h"
# include "token.h"
# include "pdata_helpers.h"

void	parse_fds(int i, int cmd_amount, t_pdata *pdata, t_token *token);

void	execute_pipe(t_pdata *pdata, t_token *token, t_context *context);

void	execute_cmd(t_pdata *pdata, t_token *token, t_context *context);

void	execute_list(t_pdata *pdata, t_token *token, t_context *context);

void	execute(t_token *token, t_context *context);

#endif
