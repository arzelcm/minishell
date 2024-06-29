/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:27 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:58:28 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "context.h"

int	ft_echo(int argc, char **argv, t_context *context)
{
	int	i;
	int	new_line;
	int	arg_len;

	(void) context;
	new_line = 1;
	i = 1;
	arg_len = ft_strlen(argv[i]);
	while (argc > 1 && i < argc && *argv[i] == '-' && arg_len > 1
		&& ft_stroccurrences(argv[i], 'n') == (int) arg_len - 1)
	{
		new_line = 0;
		i++;
		arg_len = ft_strlen(argv[i]);
	}
	while (i < argc)
	{
		ft_printf("%s", argv[i++]);
		if (i < argc)
			ft_printf(" ");
	}
	if (new_line)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
