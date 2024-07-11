/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:10 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/11 12:13:59 by cfidalgo         ###   ########.fr       */
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
		|| (var[0] == '?' && not_first && *(var - 1) != '$')
		|| (not_first && (*(var - 1) == '?')));
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
	char			*var[2];
	int				expanded;

	i = 0;
	expanded = 0;
	while (line[i])
	{
		start = i;
		if (line[i] == '$')
		{
			while (!variable_finished(line[i], i > start, &line[i]))
				i++;
			var[0] = safe_ft_substr(line, start, i - start, syserr);
			var[1] = get_var_value(var[0], context);
			push_str(new_line, var[1]);
			expanded = 1;
			free(var[0]);
			free(var[1]);
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

	new_line = safe_calloc(sizeof(char));
	expanded = replace_values(*line, &new_line, context);
	free(*line);
	*line = new_line;
	if (expansion)
		expansion->expanded = expanded;
	return (ft_strlen(new_line));
}
