/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:50:27 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/10 16:30:52 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "words.h"
#include "context.h"
#include "expansor.h"
#include "utils.h"
#include "safe_utils.h"
#include "errno.h"
#include "tokenizer.h"
#include "tokenizer_utils.h"

void	init_words(t_words	*words)
{
	words->body = ft_calloc(1, sizeof(char **));
	if (!words->body)
		syserr(ENOMEM);
	words->count = 0;
}

void	push_word(int *new_word, char *word,
	t_expansion *expansion, t_words *words)
{
	int	i;

	i = 0;
	while (i < (int) ft_strlen(word) || i == 0)
	{
		if (*new_word)
		{
			push_arg(&words->body,
				safe_ft_strdup("", syserr), &words->count);
			*new_word = 0;
		}
		if (expansion->expanded && !expansion->quoted
			&& ft_stroccurrences(" \t", word[i]))
		{
			*new_word = !words->body
				|| ft_strlen(words->body[words->count - 1]) > 0;
			avoid_spaces(word, &i);
		}
		else
			push_char(words->body + words->count - 1, word[i++]);
	}
}

void	set_words(t_words *words, char **src, t_context *context)
{
	t_expansion	expansion;
	char		*word;
	int			new_word;
	int			j;
	int			i;

	i = 0;
	while (src && src[i])
	{
		j = 0;
		new_word = 1;
		while (src[i][j])
		{
			word = get_word(src[i], &j, context, &expansion);
			if (expansion.expanded && !expansion.quoted && !*word)
			{
				free(word);
				continue ;
			}
			push_word(&new_word, word, &expansion, words);
			free(word);
		}
		i++;
	}
}
