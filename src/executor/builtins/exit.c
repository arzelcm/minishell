#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "limits.h"
#include "environment_helper.h"

int	ft_exit(int argc, char **argv, t_context *context)
{
	ft_printff(STDERR_FILENO, "exit\n");
	if (argc == 2)
	{
		if (ft_isnum(argv[1], INT_MAX))
			context->err_code = ft_atoi(argv[1]);
		else
		{
			ft_printff(STDERR_FILENO,
				"%s: exit: %s: numeric argument required\n",
				PROGRAM_NAME, argv[1]);
			context->err_code = 255;
		}
	}
	else if (argc > 2)
	{
		ft_printff(STDERR_FILENO, "%s: exit: too many arguments\n",
			PROGRAM_NAME);
		context->err_code = EXIT_FAILURE;
		return (1);
	}
	free_enviroment(&context->global_env);
	free_enviroment(&context->local_env);
	exit(context->err_code);
}
