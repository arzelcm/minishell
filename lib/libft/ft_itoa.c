/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:16:26 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 12:42:48 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_parse_result(char *s, int is_negative)
{
	char	*result;
	size_t	i;
	size_t	j;

	result = malloc(sizeof(char) * (ft_strlen(s) + 1 + is_negative));
	if (!result)
	{
		free(s);
		return (NULL);
	}
	i = ft_strlen(s) - 1;
	j = 0;
	if (is_negative)
	{
		result[j] = '-';
		j++;
	}
	while (j < ft_strlen(s) + is_negative)
		result[j++] = s[i--];
	result[j] = '\0';
	free(s);
	return (result);
}

static long	get_positive_num(int n)
{
	long	nu;

	nu = n;
	if (nu < 0)
		nu *= -1;
	return (nu);
}

static unsigned long	get_positive_lnum(long n)
{
	if (n < 0)
		return ((unsigned long) n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	i;
	long	x;
	size_t	j;

	x = get_positive_num(n);
	i = 0;
	while (x > 0)
		x /= 10 + (i++ *0);
	if (n == 0)
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	x = get_positive_num(n);
	j = 0;
	while (j < i || (j == 0 && x == 0))
	{
		result[j] = (x % 10) + '0';
		x /= 10;
		j++;
	}
	result[j] = '\0';
	return (str_parse_result(result, n < 0));
}

char	*ft_ltoa(long n)
{
	char			*result;
	size_t			i;
	unsigned long	x;
	size_t			j;

	x = get_positive_lnum(n);
	i = 0;
	while (x != 0)
		x /= 10 + (i++ *0);
	if (n == 0)
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	x = get_positive_lnum(n);
	j = 0;
	while (j < i || (j == 0 && x == 0))
	{
		result[j] = (x % 10) + '0';
		x /= 10;
		j++;
	}
	result[j] = '\0';
	return (str_parse_result(result, n < 0));
}
