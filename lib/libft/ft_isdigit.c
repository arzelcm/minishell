/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:40:40 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/03 01:16:52 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_isnum(char *str, unsigned int digits)
{
	int				is_num;
	int				symbols;
	unsigned int	digits_amount;

	symbols = 0;
	while (*str && (*str == '+' || *str == '-') && symbols == 0)
	{
		symbols++;
		str++;
	}
	digits_amount = 0;
	is_num = ft_isdigit(*str);
	while (*str && is_num && symbols <= 1)
	{
		is_num = ft_isdigit(*str) && digits_amount < digits;
		if (*str != '0')
			digits_amount++;
		str++;
	}
	return (is_num);
}
