/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:34 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 22:16:52 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes_flag.h"
#include "libft.h"
#include "utils.h"
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
	while (str[*i] != quote)
		(*i)++;
	(*i)++;
	return (1);
}

char	*quote_str(char *str)
{
	char	*tmp;
	char	*quoted_str;

	tmp = ft_strjoin("`", str);
	if (!tmp)
		handle_syserror(ENOMEM);
	quoted_str = ft_strjoin(tmp, "'");
	if (!quoted_str)
		handle_syserror(ENOMEM);
	free(tmp);
	return (quoted_str);
}

int	starting_quote(char c, t_quotes_flag *quotes)
{
	return ((c == '\"' && !quotes->double_) || (c == '\'' && !quotes->simple));
}
