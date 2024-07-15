/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:34 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/15 14:31:47 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes_flag.h"
#include "libft.h"
#include "utils.h"
#include "lexer_utils.h"
#include "meta_chars.h"
#include <errno.h>

void	check_quotes(t_quotes_flag *quotes, char c)
{
	if (c == '\'' && !quotes->double_)
		quotes->simple = !quotes->simple;
	else if (c == '\"' && !quotes->simple)
		quotes->double_ = !quotes->double_;
}

int	avoid_quotes(char *str, int *i)
{
	char	quote;

	if (str[*i] == '\"')
		quote = '\"';
	else if (str[*i] == '\'')
		quote = '\'';
	else
		return (0);
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
	return (1);
}

char	*quote_str(char *str)
{
	char	*tmp;
	char	*quoted_str;

	tmp = safe_ft_strjoin("`", str, syserr);
	if (!tmp)
		syserr(ENOMEM);
	quoted_str = safe_ft_strjoin(tmp, "'", syserr);
	if (!quoted_str)
		syserr(ENOMEM);
	free(tmp);
	return (quoted_str);
}

int	is_starting_quote(char c, t_quotes_flag *quotes)
{
	return ((c == '\"' && !quotes->double_) || (c == '\'' && !quotes->simple));
}

int	avoid_quotes_lexer(char *str, int *i, t_context *context)
{
	char	quote;

	if (str[*i] == '\"')
		quote = '\"';
	else if (str[*i] == '\'')
		quote = '\'';
	else
		return (0);
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (!str[*i])
	{
		if (quote == '\'')
			throw_syntax_error(context, S_QUOTE);
		else
			throw_syntax_error(context, D_QUOTE);
		return (-1);
	}
	(*i)++;
	return (1);
}
