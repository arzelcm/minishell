/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:40 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:58:40 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "context.h"

int	ft_pwd(int argc, char **argv, t_context *context)
{
	(void) argc;
	(void) argv;
	ft_printf("%s\n", ft_getenv("PWD", context->global_env.envp));
	return (EXIT_SUCCESS);
}
