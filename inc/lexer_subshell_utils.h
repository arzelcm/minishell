/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_subshell_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:37:23 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/07/11 15:21:39 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_SUBSHELL_UTILS_H
# define LEXER_SUBSHELL_UTILS_H

# include "context.h"

int	check_subshell_conds(char *line, int i, int *subshells, t_context *context);

#endif
