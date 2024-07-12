/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:38 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/11 14:49:27 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_UTILS_H
# define QUOTES_UTILS_H

# include "quotes_flag.h"

void	check_quotes(t_quotes_flag *quotes, char c);

int		avoid_quotes(char *str, int *i);

int		is_starting_quote(char c, t_quotes_flag *quotes);

int		avoid_quotes_lexer(char *str, int *i, t_context *context);

#endif
