#include "libft.h"
#include "expansor.h"
#include "safe_utils.h"
#include <stdlib.h>

t_var	*push_var(char *key, t_vars *vars)
{
	t_var *var;

	var = safe_calloc(sizeof(t_var));
	var->key = key;
	var->value = getenv(key + 1);
	if (!var->value)
		var->value = "";
	var->next = vars->list;
	vars->list = var;
	vars->size++;
	return (vars->list);
}

t_var	*get_var(char *key, t_vars *vars)
{
	t_var	*var;

	var = vars->list;
	while (var && ft_strcmp(var->key, key) != 0)
		var = var->next;
	if (!var)
		var = push_var(key, vars);
	else
		free(key);
	return (var);
}

void	fill_needed_vars(t_vars *vars, char *line)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			start = i;
			while (!(line[i] == '\0' || line[i] == ' '
				|| (i > start && line[i] == '$')))
				i++;
			get_var(ft_substr(line, start, i - start), &vars)->occurrences++;
			continue ;
		}
		i++;
	}
}

void	expanse(char **line)
{
	t_vars	vars;
	char	*new_line;

	ft_bzero(&vars, sizeof(t_vars));
	fill_needed_vars(&vars, *line);

	
	// TODO: Malloc apropiatte size
	// TODO: Replace keys for values
	// TODO: Free vars list
}
