/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:29 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:58:30 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "context.h"
#include "environment_helper.h"

int	ft_env(int argc, char **argv, t_context *context)
{
	if (argc > 1 && ft_strcmp(argv[1], "l") == EQUAL_STRINGS)
		print_env(context->local_env.envp);
	else
		print_env(context->global_env.envp);
	return (EXIT_SUCCESS);
}
