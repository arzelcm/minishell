/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:39 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/03 16:53:04 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "safe_utils.h"
#include "quotes_flag.h"
#include "signals.h"
#include "context.h"
#include "environment_helper.h"

void	custom_exit(t_context *context, int print)
{
	config_echoctl_terminal(ON);
	if (isatty(STDIN_FILENO) && print)
		ft_printff(STDERR_FILENO, "\033[1A%sexit\n", PROMPT);
	exit(context->err_code);
}

void	push_char(char	**str, char c)
{
	char	*new_word;
	int		len;

	len = ft_strlen(*str);
	new_word = safe_calloc(sizeof(char) * (len + 2));
	ft_strlcpy(new_word, *str, -1);
	new_word[len] = c;
	new_word[len + 1] = '\0';
	free(*str);
	*str = new_word;
}

void	handle_syserror(int errnum)
{
	perror(PROGRAM_NAME);
	exit(errnum);
}

void	handle_error(char *file, char *message)
{
	ft_printff(STDERR_FILENO, "%s: %s: ", PROGRAM_NAME, file);
	if (!message || !message[0])
		perror("");
	else
		ft_printff(STDERR_FILENO, "%s\n", message);
}
