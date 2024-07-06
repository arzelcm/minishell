/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:10 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/06 23:19:31 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansor.h"
#include "safe_utils.h"
#include "expansor_vars.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include "utils.h"
#include <stdlib.h>

int	variable_finished(char c, int not_first, char *var)
{
	return (c == '\0' || (not_first && c == '$')
		|| (!ft_isalnum(c) && !ft_stroccurrences("_?$ºª", c))
		|| (var[0] == '?' && *(var - 1) != '$'));
}

void	init_vars(t_quotes_flag *quotes, int *i, int *j)
{
	ft_bzero(quotes, sizeof(t_quotes_flag));
	*i = 0;
	if (j)
		*j = 0;
}

int
	replace_values(char *line, char **new_line, t_context *context)
{
	int				i;
	int				start;
	t_quotes_flag	quotes;
	char			*value;
	int				expanded;
	char			*key;

	init_vars(&quotes, &i, &expanded);
	while (line[i])
	{
		check_quotes(&quotes, line[i]);
		start = i;
		if (line[i] == '$' && is_starting_quote(line[i + 1], &quotes))
			i++;
		else if (line[i] == '$'
			&& (line[i + 1] != '\"' || quotes.double_) && !quotes.simple)
		{
			while (!variable_finished(line[i], i > start, &line[i]))
				i++;
			key = safe_ft_substr(line, start, i - start, handle_syserror);
			value = get_var_value(key, context);
			push_str(new_line, value);
			expanded = 1;
			free(value);
			free(key);
		}
		else
			push_char(new_line, line[i++]);
	}
	return (expanded);
}

int	expand(char **line, t_context *context, t_expansion *expansion)
{
	char	*new_line;
	int		expanded;

	if (expansion)
		ft_bzero(expansion, sizeof(t_expansion));
	if (expansion)
		expansion->quoted = (**line) == '\"';
	new_line = safe_calloc(sizeof(char));
	expanded = replace_values(*line, &new_line, context);
	free(*line);
	*line = new_line;
	if (expansion)
		expansion->expanded = expanded;
	return (ft_strlen(new_line));
}
