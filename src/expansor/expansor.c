#include "libft.h"
#include "safe_utils.h"
#include "expansor_vars.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include <stdlib.h>

void	init_expansor_vars(t_context *context)
{
	free_expansor_vars(context->vars);
	context->vars = safe_calloc(sizeof(t_vars));
}

int	variable_finished(char c, int not_first)
{
	return (c == '\0' || ft_stroccurrences(VAR_LIMIT, c)
		|| (not_first && c == '$'));
}

void
	expand_values(char *line, char *new_line, t_context *context)
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
			var = get_var(ft_substr(line, start, i - start), context);
			j += ft_strlcpy(&new_line[j], var->value, -1);
		}
		else
			new_line[j++] = line[i++];
	}
}

int	expand(char **line, t_context *context)
{
	char	*new_line;
	int		new_len;

	fill_needed_vars(*line, context);
	new_len = ft_strlen(*line) - context->vars->keys_length + context->vars->values_length;
	new_line = safe_calloc(sizeof(char) * (new_len + 1));
	expand_values(*line, new_line, context);
	free(*line);
	*line = new_line;
	ft_printf("New line: %s\n", *line);
	return (new_len);
}
