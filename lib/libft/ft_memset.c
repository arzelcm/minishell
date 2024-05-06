/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:44:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/01/16 19:14:04 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	uc;
	size_t			i;

	uc = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		((char *) b)[i] = uc;
		i++;
	}
	return (b);
}
