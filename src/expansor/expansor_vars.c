#include "expansor_vars.h"
#include "libft.h"
#include "safe_utils.h"
#include "expansor.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include "environment.h"

char	*get_var_value(char *key, t_context *context)
{
	char	*value;

	value = ft_getenv(key + 1, context->global_env.envp);
	if (!value)
	{
		if (ft_strcmp(key, "$") == EQUAL_STRINGS)
			value = ft_strdup(key);
		else if (ft_strcmp(key, "$?") == EQUAL_STRINGS)
			value = ft_itoa(context->err_code);
	}
	else
		value = ft_strdup(value);
	return (value);
}

t_var	*push_var(char *key, t_vars *vars, t_context *context)
{
	t_var	*var;

	var = safe_calloc(sizeof(t_var));
	var->key = key;
	var->value = get_var_value(key, context);
	var->next = vars->list;
	vars->list = var;
	vars->size++;
	return (vars->list);
}

t_var	*get_var(char *key, t_vars *vars, t_context *context)
{
	t_var	*var;

	var = vars->list;
	while (var && ft_strcmp(var->key, key) != 0)
		var = var->next;
	if (!var)
		var = push_var(key, vars, context);
	else
		free(key);
	return (var);
}

void	fill_needed_vars(t_vars *vars, char *line, t_context *context)
{
	int				i;
	int				start;
	t_var			*var;
	t_quotes_flag	quotes;

	ft_bzero(&quotes, sizeof(t_quotes_flag));
	i = 0;
	start = 0;
	while (line[i])
	{
		check_quotes(&quotes, line[i]);
		if (line[i] == '$' && line[i + 1] != '\"' && !quotes.simple)
		{
			start = i;
			while (!variable_finished(line[i], i > start))
				i++;
			var = get_var(ft_substr(line, start, i - start), vars, context);
			vars->keys_length += ft_strlen(var->key);
			vars->values_length += ft_strlen(var->value);
		}
		else
			i++;
		if (line[i] == '$' && (line[i + 1] == '\"' || line[i + 1] == '\''))
			vars->keys_length -= 1;
	}
}

void	free_expansor_vars(t_var *var)
{
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
