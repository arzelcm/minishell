/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:10 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/30 00:36:44 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansor.h"
#include "safe_utils.h"
#include "expansor_vars.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include <stdlib.h>

int	variable_finished(char c, int not_first)
{
	return (c == '\0' || ft_stroccurrences(VAR_LIMIT, c)
		|| (not_first && c == '$'));
}

void	init_vars(t_quotes_flag *quotes, int *i, int *j)
{
	ft_bzero(quotes, sizeof(t_quotes_flag));
	*i = 0;
	*j = 0;
}

void
	expand_values(char *line, char *new_line, t_vars *vars, t_context *context)
{
	int				i;
	int				j;
	int				start;
	t_quotes_flag	quotes;
	t_var			*var;

	init_vars(&quotes, &i, &j);
	while (line[i])
	{
		check_quotes(&quotes, line[i]);
		start = i;
		if (line[i] == '$' && is_starting_quote(line[i + 1], &quotes))
			i++;
		else if (line[i] == '$'
			&& (line[i + 1] != '\"' || quotes.double_) && !quotes.simple)
		{
			while (!variable_finished(line[i], i > start))
				i++;
			var = get_var(ft_substr(line, start, i - start), vars, context);
			j += ft_strlcpy(&new_line[j], var->value, -1);
		}
		else
			new_line[j++] = line[i++];
	}
}

int	expand(char **line, t_context *context, t_expansion *expansion)
{
	t_vars	vars;
	char	*new_line;
	int		new_len;

	ft_bzero(&vars, sizeof(t_vars));
	if (expansion)
		ft_bzero(expansion, sizeof(t_expansion));
	if (expansion)
		expansion->quoted = (**line) == '\"';
	fill_needed_vars(&vars, *line, context);
	new_len = ft_strlen(*line) - vars.keys_length + vars.values_length;
	new_line = safe_calloc(sizeof(char) * (new_len + 1));
	expand_values(*line, new_line, &vars, context);
	free(*line);
	*line = new_line;
	if (expansion)
		expansion->expanded = vars.size;
	free_expansor_vars(vars.list);
	return (new_len);
}
