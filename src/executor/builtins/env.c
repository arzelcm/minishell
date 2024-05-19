#include "libft.h"
#include "context.h"
#include "environment_helper.h"

int	ft_env(int argc, char **argv, t_context *context)
{
	(void) argc;
	(void) argv;
	print_env(&context->env);
	return (1);
}