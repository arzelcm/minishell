/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:57:56 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

# include "context.h"
# include "expansor.h"

int		avoid_spaces(char *str, int *i);

char	*get_word(char	*str, int *i, t_context *context,
			t_expansion *expansion);

char	*get_raw_word(char	*str, int *i);

#endif