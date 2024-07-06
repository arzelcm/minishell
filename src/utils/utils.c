/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:39 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/06 23:05:48 by arcanava         ###   ########.fr       */
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

void	push_str(char **s1, char *s2)
{
	char	*new_word;
	int		len1;
	int		len2;

	len1 = ft_strlen(*s1);
	len2 = ft_strlen(s2);
	new_word = safe_calloc(sizeof(char) * (len1 + len2 + 1));
	ft_strlcpy(new_word, *s1, -1);
	ft_strlcpy(new_word + len1, s2, -1);
	free(*s1);
	*s1 = new_word;
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
