/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/03 18:38:06 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansor_vars.h"
#include "libft.h"
#include "safe_utils.h"
#include "expansor.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include "environment.h"
#include "safe_libft.h"
#include "utils.h"

char	*get_var_value(char *key, t_context *context)
{
	char	*value;

	value = ft_getenv(key + 1, context->global_env.envp);
	if (!value)
	{
		if (ft_strcmp(key, "$") == EQUAL_STRINGS)
			value = safe_ft_strdup(key, handle_syserror);
		else if (ft_strcmp(key, "$?") == EQUAL_STRINGS)
			value = safe_itoa(context->err_code);
	}
	else
		value = safe_ft_strdup(value, handle_syserror);
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

	init_vars(&quotes, &i, &start);
	while (line[i])
	{
		check_quotes(&quotes, line[i]);
		if (line[i] == '$'
			&& (quotes.double_ || line[i + 1] != '\"') && !quotes.simple)
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
		if (line[i] == '$' && is_starting_quote(line[i + 1], &quotes))
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
