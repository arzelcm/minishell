/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:18 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/10 20:55:03 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H
# include "context.h"

int		is_redirection(char *line, int index);

void	throw_syntax_error(t_context *context, char *metachars);

int		check_metachar(t_context *context, char *line, int i);

int		check_pipe_error(t_context *context, char *line, int i);

#endif
