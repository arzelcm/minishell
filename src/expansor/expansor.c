#include "libft.h"
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

void
	expand_values(char *line, char *new_line, t_vars *vars, t_context *context)
{
	int				i;
	int				j;
	int				start;
	t_quotes_flag	quotes;
	t_var			*var;

	ft_bzero(&quotes, sizeof(t_quotes_flag));
	i = 0;
	j = 0;
	while (line[i])
	{
		check_quotes(&quotes, line[i]);
		if (line[i] == '$' && !quotes.simple)
		{
			start = i;
			while (!variable_finished(line[i], i > start))
				i++;
			var = get_var(ft_substr(line, start, i - start), vars, context);
			j += ft_strlcpy(&new_line[j], var->value, -1);
		}
		else
			new_line[j++] = line[i++];
	}
}

void	expand(char **line, t_context *context)
{
	t_vars	vars;
	char	*new_line;

	ft_bzero(&vars, sizeof(t_vars));
	fill_needed_vars(&vars, *line, context);
	new_line = safe_calloc(sizeof(char)
			* (ft_strlen(*line) - vars.keys_length + vars.values_length));
	expand_values(*line, new_line, &vars, context);
	free(*line);
	*line = new_line;
	ft_printf("New line: %s\n", *line);
	free_expansor_vars(vars.list);
}
