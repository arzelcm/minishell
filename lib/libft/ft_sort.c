/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:58:09 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 17:05:21 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matrix_sort(char **matrix)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[j])
		{
			if (ft_strcmp(matrix[i], matrix[j]) < 0)
			{
				aux = matrix[j];
				matrix[j] = matrix[i];
				matrix[i] = aux;
			}
			j++;
		}
		i++;
	}
}
