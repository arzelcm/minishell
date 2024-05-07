/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:08:54 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/07 14:21:58 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	(void) envp;
	if (argc > 1)
		return (EXIT_FAILURE);
	ft_printf("Hello amatist!\n");
	while (42)
	{
		char *newline = readline("Amatist> ");
		ft_printf("Read: %s\n", newline);
	}
	return (EXIT_SUCCESS);
}