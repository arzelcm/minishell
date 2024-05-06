/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stroccurrences.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:32:35 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:51:27 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_stroccurrences(char *str, char c)
{
	int	occurrences;

	occurrences = 0;
	while (str && *str)
	{
		if (*str == c)
			occurrences++;
		str++;
	}
	return (occurrences);
}
