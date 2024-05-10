#include "libft.h"
#include "expansor.h"
#include "safe_utils.h"
#include <stdlib.h>

char	*get_var_value(char *key)
{
	char	*value;

	value = getenv(key + 1);
	if (!value)
	{
		if (ft_strlen(key) == 1)
			value = ft_strdup(key);
		// TODO: Search for local vars
	}
	else
		value = ft_strdup(value);
	return (value);
}

t_var	*push_var(char *key, t_vars *vars)
{
	t_var	*var;

	var = safe_calloc(sizeof(t_var));
	var->key = key;
	var->value = get_var_value(key);
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
	t_var	*var;

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
			var = get_var(ft_substr(line, start, i - start), vars);
			vars->keys_length += ft_strlen(var->key);
			vars->values_length += ft_strlen(var->value);
			continue ;
		}
		i++;
	}
}

void free_vars_list(t_var *var) {
	t_var	*aux;

	while (var)
	{
		aux = var;
		var = var->next;
		free(aux->key);
		free(aux->value);
		free(aux);
	}
}

void	expanse(char **line)
{
	t_vars	vars;
	char	*new_line;

	ft_bzero(&vars, sizeof(t_vars));
	fill_needed_vars(&vars, *line);
	new_line = safe_calloc(sizeof(char)
			* (ft_strlen(*line) - vars.keys_length + vars.values_length));
	// TODO: Replace keys for values
	free(*line);
	*line = new_line;
	free_vars_list(vars.list);
}
