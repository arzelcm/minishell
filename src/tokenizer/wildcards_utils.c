/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:23:32 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/16 19:14:37 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	compare_pattern_str(char *str, char *pattern)
{
	return (ft_strncmp(str, pattern,
			ft_strlen(pattern) - ft_strlen(ft_strchr(pattern, '*'))));
}

int	check_corner_cases(char *pattern, char *str)
{
	char	c;

	if (*str && *pattern && *pattern != '*'
		&& compare_pattern_str(str, pattern) != EQUAL_STRINGS)
		return (0);
	c = *(ft_strrchr(pattern, '*') + 1);
	if (*str && *pattern && c != '\0')
		if (!ft_strrchr(str, c)
			|| ft_strcmp(ft_strrchr(str, c),
				ft_strrchr(pattern, '*') + 1) != EQUAL_STRINGS)
			return (0);
	if (*pattern != '*' && (compare_pattern_str(str, pattern) == EQUAL_STRINGS
			&& (!ft_strrchr(str + 1, c) || ft_strcmp(ft_strrchr(str + 1, c),
					ft_strrchr(pattern, '*') + 1) != EQUAL_STRINGS)))
		return (0);
	return (1);
}
