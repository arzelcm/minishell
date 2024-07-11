/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_subshell_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:36:17 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/07/11 14:40:12 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "meta_chars.h"

int	check_close_subsh(t_context *context, char *line, int index, int i)
{
	char	*token;

	while (i >= 0)
	{
		if (line[i] != ' ' && line[i] != '\t')
			break ;
		i--;
	}
	if (i < 0)
		return (throw_syntax_error(context, CLOSE_SUBSHELL), 0);
	i = index + 1;
	while (line[i])
	{
		if (line[i] == OPEN_SUBSHELL[0])
			return (throw_syntax_error(context, OPEN_SUBSHELL), 0);
		if (line[i] != ' ' && line[i] != '\t')
			break ;
		i++;
	}
	if (line[i] != '\0' && line[i] != PIPE[0] && line[i] != AND[0]
		&& line[i] != HERE_DOC_RD[0] && line[i] != APPEND_RD[0]
		&& line[i] != CLOSE_SUBSHELL[0])
	{
		token = get_raw_word(line, &i);
		return (throw_syntax_error(context, token), free(token), 0);
	}
	return (1);
}

int	check_open_subsh(t_context *context, char *line, int index, int i)
{
	while (i >= 0)
	{
		if (line[i] != ' ' && line[i] != '\t')
			break ;
		i--;
	}
	if (i >= 0 && line[i] != PIPE[0] && line[i] != AND[0]
		&& line[i] != OPEN_SUBSHELL[0])
		return (throw_syntax_error(context, OPEN_SUBSHELL), 0);
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
