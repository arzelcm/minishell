#include "libft.h"
#include "context.h"
#include "environment_helper.h"

int	ft_exit(int argc, char **argv, t_context *context)
{
	(void) argc;
	(void) argv;
	free_enviroment(&context->global_env);
	free_enviroment(&context->local_env);
	exit(EXIT_SUCCESS);
}