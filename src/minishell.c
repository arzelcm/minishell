/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:08:54 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/07 14:14:10 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>

int	main(void)
{
	ft_printf("Hello amatist!\n");
	while (42)
	{
		char *newline = readline("Amatist> ");
		ft_printf("Read: %s\n", newline);
	}
	return (EXIT_SUCCESS);
}