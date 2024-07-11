/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:17 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/10 21:33:59 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "lexer_utils.h"
#include "meta_chars.h"
#include "quotes_flag.h"
#include "quotes_utils.h"

// TODO: Move it to a function
static int	check_pipe(t_context *context, char *line, int index)
{
	int	i;

	if (line[index] != PIPE[0] || !ft_strncmp(&line[index], OR, AND_OR_LENGTH))
		return (1);
	i = index - 1;
	while (i >= 0)
	{
		if (line[i] != ' ' && line[i] != '\t')
			break ;
		i--;
	}
	if (i < 0)
		return (throw_syntax_error(context, PIPE), 0);
	i = index + 1;
	while (line[i])
	{
		if (!check_pipe_error(context, line, i))
			return (0);
		else if (line[i] != ' ' && line[i] != '\t')
			break ;
		i++;
	}
	if (line[i] == '\0')
		return (throw_syntax_error(context, "newline"), 0);
	return (1);
}

static int	check_redirection(t_context *context, char *line, int index)
{
	int	i;

	if (!is_redirection(line, index))
		return (1);
	i = index + 1;
	if ((line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0])
		|| (line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0]))
		i++;
	while (line[i])
	{
		if (!check_metachar(context, line, i))
			return (0);
		else if (line[i] != ' ' && line[i] != '\t')
			break ;
		i++;
	}
	if (line[i] == '\0')
		return (throw_syntax_error(context, "newline"), 0);
	return (1);
}

static int	check_and_or(t_context *context, char *line, int index)
{
	int	i;

	if (ft_strncmp(&line[index], AND, AND_OR_LENGTH) != EQUAL_STRINGS
		&& ft_strncmp(&line[index], OR, AND_OR_LENGTH) != EQUAL_STRINGS)
		return (1);
	i = index - 1;
	while (i >= 0)
	{
		if (line[i] != ' ' && line[i] != '\t')
			break ;
		i--;
	}
	if (i < 0)
		return (check_pipe_error(context, line, index));
	i = index + 1;
	while (line[++i])
	{
		if (!check_pipe_error(context, line, i))
			return (0);
		else if (line[i] != ' ' && line[i] != '\t')
			break ;
	}
	if (line[i] == '\0')
		return (throw_syntax_error(context, "newline"), 0);
	return (1);
}

int	check_syntax(t_context *context, char *line)
{
	t_quotes_flag	quotes;
	int				i;

	ft_bzero(&quotes, sizeof(t_quotes_flag));
	i = 0;
	while (line[i])
	{
		check_quotes(&quotes, line[i]);
		if (!quotes.double_ && !quotes.simple && !check_pipe(context, line, i))
			return (0);
		if (!quotes.double_ && !quotes.simple
			&& !check_redirection(context, line, i))
			return (0);
		if (!quotes.double_ && !quotes.simple
			&& !check_and_or(context, line, i))
			return (0);
		i++;
	}
	if (quotes.double_)
		return (throw_syntax_error(context, D_QUOTE), 0);
	else if (quotes.simple)
		return (throw_syntax_error(context, S_QUOTE), 0);
	return (1);
}
