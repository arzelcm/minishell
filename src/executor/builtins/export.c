/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:35 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/05 12:02:56 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "environment_helper.h"
#include "tokenizer.h"
#include "tokenizer_utils.h"
#include "builtins.h"
#include "safe_utils.h"
#include "utils.h"

void	set_complete_definition(char *curr_def, char **key_value)
{
	char	*key;
	char	*value;
	char	*complete_val;

	key = ft_substr(curr_def, 0, ft_strchr(curr_def, '=') - curr_def);
	value = ft_substr(ft_strchr(curr_def, '='), 1, ft_strlen(curr_def));
	if (value)
	{
		complete_val = safe_ft_strjoin("=\"", value, handle_syserror);
		free(value);
		value = safe_ft_strjoin(complete_val, "\"", handle_syserror);
		free(complete_val);
		complete_val = value;
		value = NULL;
	}
	else
		complete_val = safe_ft_strdup("=\"\"", handle_syserror);
	*key_value = safe_ft_strjoin(key, complete_val, handle_syserror);
	free(complete_val);
	free(value);
	free(key);
}

static void	fill_definitions(char **definitions, int *i, char **envp)
{
	char	*key_value;
	int		j;

	j = 0;
	while (envp[j])
	{
		if (ft_stroccurrences(envp[j], '='))
			set_complete_definition(envp[j], &key_value);
		else
			key_value = safe_ft_strdup(envp[j], handle_syserror);
		j++;
		definitions[(*i)++] = safe_ft_strjoin("declare -x ", key_value,
				handle_syserror);
		free(key_value);
	}
	definitions[*i] = NULL;
}

static void	print_definitions(t_context *context)
{
	char	**definitions;
	int		i;

	definitions = safe_calloc(sizeof(char *)
			* (context->global_env.size + context->local_env.size + 1));
	i = 0;
	fill_definitions(definitions, &i, context->global_env.envp);
	fill_definitions(definitions, &i, context->local_env.envp);
	ft_matrix_sort(definitions);
	print_env(definitions);
	free_matrix(definitions);
}

// TODO: Add += compatibility
static int	has_errors(char *str, int *i, t_context *context)
{
	if ((!ft_isalpha(*str) && *str != '_')
		|| (!ft_stroccurrences(str, '=') && ft_stroccurrences_set(str, " \t"))
		|| !check_invalid_chars(str))
	{
		ft_printff(STDERR_FILENO,
			"%s: export: `%s': not a valid identifier\n", PROGRAM_NAME, str);
		context->err_code = EXIT_FAILURE;
		(*i)++;
		return (1);
	}
	else
		return (0);
}

int	ft_export(int argc, char **argv, t_context *context)
{
	int		i;
	int		export_mode;
	char	*key;
	char	*value;

	context->err_code = EXIT_SUCCESS;
	if (argc == 1)
		print_definitions(context);
	i = 1;
	while (i < argc && argv[i])
	{
		if (has_errors(argv[i], &i, context))
			continue ;
		key = get_key(argv[i], &export_mode);
		value = safe_ft_substr(ft_strchr(argv[i], '='), 1,
				ft_strlen(argv[i]), handle_syserror);
		if (!value && argv[i][ft_strlen(argv[i]) - 1] == '=')
			value = safe_ft_strdup("", handle_syserror);
		update_env(key, value, export_mode, context);
		free(key);
		free(value);
		i++;
	}
	return (context->err_code);
}
