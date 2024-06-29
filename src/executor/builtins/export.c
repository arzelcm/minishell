/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:35 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:58:35 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "environment_helper.h"
#include "tokenizer.h"
#include "tokenizer_utils.h"
#include "safe_utils.h"

void	set_complete_definition(char *curr_def, char **key_value)
{
	char	*key;
	char	*value;
	char	*complete_val;
	char	**complete;

	complete = ft_split(curr_def, '=');
	key = complete[0];
	value = complete[1];
	free(complete);
	if (value)
	{
		complete_val = ft_strjoin("=\"", value);
		free(value);
		value = ft_strjoin(complete_val, "\"");
		free(complete_val);
		complete_val = value;
		value = NULL;
	}
	else
		complete_val = ft_strdup("=\"\"");
	*key_value = ft_strjoin(key, complete_val);
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
			key_value = ft_strdup(envp[j]);
		j++;
		definitions[(*i)++] = ft_strjoin("declare -x ", key_value);
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

static int	has_errors(char *str, int *i, t_context *context)
{
	if (!ft_isalpha(*str))
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
	char	*key;
	char	*value;
	char	**splitted;

	context->err_code = EXIT_SUCCESS;
	if (argc == 1)
		print_definitions(context);
	i = 1;
	while (i < argc && argv[i])
	{
		if (has_errors(argv[i], &i, context))
			continue ;
		splitted = ft_split(argv[i], '=');
		key = splitted[0];
		value = splitted[1];
		free(splitted);
		if (!value && argv[i][ft_strlen(argv[i]) - 1] == '=')
			value = ft_strdup("");
		ft_putenv(key, value, context);
		free(key);
		free(value);
		i++;
	}
	return (context->err_code);
}
