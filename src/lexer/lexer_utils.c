/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:14 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/10 21:05:39 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "meta_chars.h"

int	is_redirection(char *line, int index)
{
	return (line[index] == INPUT_RD[0]
		|| line[index] == OUTPUT_RD[0]
		|| (line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0])
		|| (line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0]));
}

void	throw_syntax_error(t_context *context, char *metachars)
{
	ft_printff(STDERR_FILENO, \
		"amethyst: syntax error near unexpected token `%s'\n", metachars);
	context->err_code = SYNTAX_ERROR;
}

int	check_pipe_error(t_context *context, char *line, int i)
{
	if (ft_strncmp(&line[i], AND, AND_OR_LENGTH) == EQUAL_STRINGS)
		return (throw_syntax_error(context, AND), 0);
	else if (ft_strncmp(&line[i], OR, AND_OR_LENGTH) == EQUAL_STRINGS)
		return (throw_syntax_error(context, OR), 0);
	else if (line[i] == PIPE[0])
		return (throw_syntax_error(context, PIPE), 0);
	return (1);
}

int	check_metachar(t_context *context, char *line, int i)
{
	if (!check_pipe_error(context, line, i))
		return (0);
	else if (line[i] == INPUT_RD[0] && line[i + 1] == INPUT_RD[0])
		return (throw_syntax_error(context, HERE_DOC_RD), 0);
	else if (line[i] == OUTPUT_RD[0] && line[i + 1] == OUTPUT_RD[0])
		return (throw_syntax_error(context, APPEND_RD), 0);
	else if (line[i] == INPUT_RD[0])
		return (throw_syntax_error(context, INPUT_RD), 0);
	else if (line[i] == OUTPUT_RD[0])
		return (throw_syntax_error(context, OUTPUT_RD), 0);
	return (1);
}
