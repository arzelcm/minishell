#include "libft.h"
#include "context.h"
#include "environment_helper.h"

int	ft_env(int argc, char **argv, t_context *context)
{
	(void) argv;
	
	if (argc > 1 && ft_strcmp(argv[1], "l") == EQUAL_STRINGS)
		print_env(context->local_env.envp);
	else
		print_env(context->global_env.envp);
	return (1);
}