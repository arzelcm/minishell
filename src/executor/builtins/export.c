#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "environment_helper.h"
#include "tokenizer.h"
#include "tokenizer_utils.h"
#include "safe_utils.h"

// TODO: Environment local getters
// TODO: Leaks
// TODO: Search duplicates on local or global and replace when needed, NONE CAN BE DUPLICATED

static void	fill_definitions(char **definitions, int *i, char **envp)
{
	char	*key;
	char	*value;
	char	*complete_val;
	char	**complete;
	char	*key_value;
	int		j;

	j = 0;
	while (envp[j])
	{
		if (ft_stroccurrences(envp[j], '='))
		{
			complete = ft_split(envp[j], '=');
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
			key_value = ft_strjoin(key, complete_val);
			free(complete_val);
			free(value);
			free(key);
		}
		else
			key_value = ft_strdup(envp[j]);
		j++;
		definitions[(*i)++] = ft_strjoin("declare -x ", key_value);
		free(key_value);
	}
	definitions[*i] = NULL;
}

static void	sort_definitions(char **definitions)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (definitions[i])
	{
		j = 0;
		while (definitions[j])
		{
			if (ft_strcmp(definitions[i], definitions[j]) < 0)
			{
				aux = definitions[j];
				definitions[j] = definitions[i];
				definitions[i] = aux;
			}
			j++;
		}
		i++;
	}
}

static void	print_definitions(t_context *context)
{
	char	**definitions;
	int		i;

	definitions = safe_calloc(sizeof(char *) * (context->global_env.size + context->local_env.size + 1));
	i = 0;
	fill_definitions(definitions, &i, context->global_env.envp);
	fill_definitions(definitions, &i, context->local_env.envp);
	sort_definitions(definitions);
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
	char	**arg;

	i = 0;
	if (ft_strcmp(argv[i], "export") == EQUAL_STRINGS)
	{
		if (argc == 1)
			print_definitions(context);
		i++;
	}
	while (i < argc && argv[i])
	{
		if (has_errors(argv[i], &i, context))
			continue ;
		arg = ft_split(argv[i], '=');
		key = arg[0];
		value = arg[1];
		if (!value && argv[i][ft_strlen(argv[i]) - 1] == '=')
			value = ft_strdup("");
		if (value)
			ft_putenv(key, value, &context->global_env);
		else
			ft_putenv(key, value, &context->local_env);
		free(arg);
		free(key);
		free(value);
		i++;
	}
	return(1);
}
