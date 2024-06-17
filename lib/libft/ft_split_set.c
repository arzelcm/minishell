/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:18:59 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/15 18:03:07 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**add_new_str(char **str, char *new_str)
{
	size_t		i;
	size_t		j;
	char		**result;

	i = 0;
	while (str[i] != NULL)
		i++;
	result = malloc(sizeof(char *) * (i + (ft_strlen(new_str) > 0) + 1));
	if (!result)
	{
		free_matrix(str);
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = new_str;
	result[j + 1] = NULL;
	free(str);
	return (result);
}

static char	**store_string(char const *s, size_t st, size_t ri, char **ss)
{
	char	*new_str;

	if (ri > 0)
	{
		new_str = ft_substr(s, (unsigned int) st, ri);
		if (!new_str)
		{
			free_matrix(ss);
			return (NULL);
		}
		ss = add_new_str(ss, new_str);
		if (!ss)
		{
			free(new_str);
			free_matrix(ss);
			return (NULL);
		}
	}
	return (ss);
}

char	**ft_split_set(char const *s, char const *set)
{
	size_t	i;
	size_t	start;
	char	**strings;

	if (!s || !set)
		return (NULL);
	i = 0;
	start = 0;
	strings = malloc(sizeof(char *));
	if (!strings)
		return (NULL);
	strings[0] = NULL;
	while (s[i] != '\0')
	{
		if (ft_stroccurrences((char *) set, s[i]))
		{
			strings = store_string(s, start, i - start, strings);
			if (!strings)
				return (NULL);
			start = i + 1;
		}
		i++;
	}
	strings = store_string(s, start, i - start, strings);
	return (strings);
}
