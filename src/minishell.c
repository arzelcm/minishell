/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:08:54 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/07 14:29:43 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>
 #include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	char	*curr_line;

	(void) argv;
	(void) envp;
	if (argc > 1)
		return (EXIT_FAILURE);
	while (42)
	{
		curr_line = readline("Amatist> ");
		free(curr_line);
	}
	return (EXIT_SUCCESS);
}