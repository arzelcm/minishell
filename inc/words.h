/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:51:01 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/09 19:58:21 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORDS_H
# define WORDS_H

typedef struct	s_words
{
	int		*count;
	char	**body;
}			t_words;

typedef struct	s_context	t_context;

void	set_words(t_words *words, char **src, t_context *context);

void	init_words(t_words	*words);

#endif