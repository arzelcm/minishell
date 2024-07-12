/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:06 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/12 16:24:47 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "context.h"
# include "token.h"
# include "pdata_helpers.h"

void	execute_subshell(t_pdata *pdata, t_token *token, t_context *context);

void	execute_pipe(t_token *token, t_context *context);

void	execute_cmd(t_token *token, t_context *context);

void	execute_list(t_token *token, t_context *context);

void	execute(t_token *token, t_context *context);

#endif
