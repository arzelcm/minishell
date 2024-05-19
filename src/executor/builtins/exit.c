#include "libft.h"
#include "context.h"
#include "environment_helper.h"

int	ft_exit(int argc, char **argv, t_context *context)
{
	(void) argc;
	(void) argv;
	free_enviroment(&context->env);
	exit(EXIT_SUCCESS);
}