#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "environment_helper.h"
#include "tokenizer.h"
#include "tokenizer_utils.h"

// TODO: Enviroment local getters
// TODO: Empty export sorted
// TODO: Leaks

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
			ft_printf("Printing declarations\n");
		i++;
	}
	while (i < argc && argv[i])
	{
		if (!ft_isalpha(*argv[i]))
		{
			ft_printff(STDERR_FILENO,
				"%s: export: `%s': not a valid identifier\n", PROGRAM_NAME, argv[i]);
			context->err_code = EXIT_FAILURE;
			i++;
			continue;
		}
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
