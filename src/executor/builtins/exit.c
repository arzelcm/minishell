#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "environment_helper.h"

int	ft_exit(int argc, char **argv, t_context *context)
{
	if (argc > 2)
	{
		ft_printff(STDERR_FILENO, "%s: exit: too many arguments\n", PROGRAM_NAME);
		context->err_code = EXIT_FAILURE;
		return (1);
 	}
	if (argc == 2)
		context->err_code = ft_atoi(argv[1]);
	free_enviroment(&context->global_env);
	free_enviroment(&context->local_env);
	ft_printff(STDERR_FILENO, "exit\n");
	exit(context->err_code);
}
