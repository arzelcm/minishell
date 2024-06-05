/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:40:40 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/05 11:46:02 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_isnum(char *str, long long max)
{
	int				is_num;
	int				symbols;
	unsigned int	digits_amount;
	unsigned int	digits;
	long long		num;

	digits = count_ull_digits(max);
	num = ft_atoll(str);
	symbols = 0;
	while (*str && (*str == '+' || *str == '-') && symbols++ == 0)
		str++;
	while (*str && *str == '0')
		str++;
	digits_amount = 0;
	is_num = ft_isdigit(*str);
	while (*str && is_num && symbols <= 1)
	{
		is_num = ft_isdigit(*str) && digits_amount < digits;
		digits_amount++;
		str++;
	}
	return (is_num && num <= max);
}
