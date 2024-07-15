/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:23:32 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/15 22:28:01 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	compare_pattern_str(char *str, char *pattern)
{
	return (ft_strncmp(str, pattern,
			ft_strlen(pattern) - ft_strlen(ft_strchr(pattern, '*'))));
}
