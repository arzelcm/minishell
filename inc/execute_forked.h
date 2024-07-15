/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_forked.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:58:08 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/07/15 18:13:37 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_FORKED_H
# define EXECUTE_FORKED_H

#include "pdata_helpers.h"
#include <stdlib.h>

void	execute_forked_subshell(
	t_token *curr_token, t_token *token, t_pdata *pdata, t_context *context);

void	execute_forked_pipe(
	pid_t *pids, t_pdata *pdata, t_token *token, t_context *context);

void	clean_pipe(pid_t *pids, t_token *token, t_context *context);

#endif
