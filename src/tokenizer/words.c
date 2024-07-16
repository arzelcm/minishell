/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:50:27 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/16 19:22:25 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "words.h"
#include "context.h"
#include "expansor.h"
#include "utils.h"
#include "safe_utils.h"
#include "errno.h"
#include "tokenizer.h"
#include "tokenizer_utils.h"
#include "wildcards_utils.h"
#include <sys/types.h>
#include <dirent.h>

void	init_words(t_words	*words)
{
	words->body = ft_calloc(1, sizeof(char **));
	if (!words->body)
		syserr(ENOMEM);
	words->count = 0;
}

int	matches_pattern(char *pattern, char *str)
{
	if (!check_corner_cases(pattern, str))
		return (0);
	pattern = ft_strchr(pattern, '*');
	while (pattern && *pattern && (pattern != ft_strrchr(pattern, '*')))
	{
		while (*pattern == '*')
			pattern++;
		while (*str && compare_pattern_str(str, pattern) != EQUAL_STRINGS)
			str++;
		if (!*str)
			return (0);
		pattern = ft_strchr(pattern, '*');
	}
	return (1);
}

void	push_wildcard_results(char *word, t_words *words)
{
	DIR				*dir_stream;
	struct dirent	*dir_results;
	int				old_word_count;

	old_word_count = words->count;
	dir_stream = opendir(".");
	if (!dir_stream)
		syserr(EBADF);
	dir_results = readdir(dir_stream);
	while (dir_results != NULL)
	{
		if (*dir_results->d_name != '.'
			&& matches_pattern(word, dir_results->d_name))
			push_arg(&words->body, safe_ft_strdup(dir_results->d_name, syserr),
				&words->count);
		dir_results = readdir(dir_stream);
	}
	if (old_word_count == words->count)
		push_arg(&words->body, safe_ft_strdup(word, syserr), &words->count);
	ft_matrix_sort_lc(words->body + old_word_count);
	closedir(dir_stream);
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
			if (*word && !expansion.quoted && ft_stroccurrences(word, '*'))
				push_wildcard_results(word, words);
			else if (*word || !expansion.expanded || expansion.quoted)
				push_word(&new_word, word, &expansion, words);
			free(word);
		}
		i++;
	}
}
