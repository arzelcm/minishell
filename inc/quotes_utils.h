/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:38 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:57:39 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_UTILS_H
# define QUOTES_UTILS_H

# include "quotes_flag.h"

void	check_quotes(t_quotes_flag *quotes, char c);

int		avoid_quotes(char *str, int *i);

#endif