/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:42 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:58:43 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "environment.h"

static int	has_errors(char *str, int *i, t_context *context)
{
	if (!ft_isalpha(*str))
	{
		ft_printff(STDERR_FILENO,
			"%s: unset: `%s': not a valid identifier\n", PROGRAM_NAME, str);
		context->err_code = EXIT_FAILURE;
		(*i)++;
		return (1);
	}
	else
		return (0);
}

int	ft_unset(int argc, char **argv, t_context *context)
{
	int	i;

	context->err_code = EXIT_SUCCESS;
	i = 1;
	while (i < argc && argv[i])
	{
		if (has_errors(argv[i], &i, context))
			continue ;
		if (!ft_deleteenv(argv[i], &context->local_env))
			ft_deleteenv(argv[i], &context->global_env);
		i++;
	}
	return (context->err_code);
}
