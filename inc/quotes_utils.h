/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:38 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 22:17:05 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_UTILS_H
# define QUOTES_UTILS_H

# include "quotes_flag.h"

void	check_quotes(t_quotes_flag *quotes, char c);

int		avoid_quotes(char *str, int *i);

int		starting_quote(char c, t_quotes_flag *quotes);

#endif