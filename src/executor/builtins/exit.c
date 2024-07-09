/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:31 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/09 23:26:16 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer_utils.h"
#include "libft.h"
#include "context.h"
#include "limits.h"
#include "environment_helper.h"
#include "builtins.h"
#include "utils.h"
#include <errno.h>

static void	throw_err_numeric_argument(char **argv, t_context *context)
{
	ft_printff(STDERR_FILENO,
		"%s: exit: %s: numeric argument required\n",
		PROGRAM_NAME, argv[1]);
	context->err_code = ABNORMAL_EXIT_STATUS;
	custom_exit(context, 0);
}

int	ft_exit(int argc, char **argv, t_context *context)
{
	char	*trimed_arg;

	if (isatty(STDIN_FILENO))
		ft_printff(STDERR_FILENO, "exit\n");
	if (argc > 1)
	{
		trimed_arg = safe_ft_strtrim(argv[1], " \t", syserr);
		if (!trimed_arg)
			syserr(ENOMEM);
		if (ft_isnum_lim(trimed_arg, LLONG_MAX, LLONG_MIN))
			context->err_code = ft_atoi(argv[1]);
		else
			throw_err_numeric_argument(argv, context);
		free(trimed_arg);
	}
	if (argc > 2)
	{
		handle_error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	custom_exit(context, 0);
	return (EXIT_SUCCESS);
}
