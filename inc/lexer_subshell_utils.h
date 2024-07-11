/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_subshell_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:37:23 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/07/11 14:41:05 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_SUBSHELL_UTILS_H
# define LEXER_SUBSHELL_UTILS_H

# include "context.h"

int	check_close_subsh(t_context *context, char *line, int index, int i);

int	check_open_subsh(t_context *context, char *line, int index, int i)

#endif
