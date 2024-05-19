#include "libft.h"
#include "context.h"

int	ft_pwd(int argc, char **argv, t_context *context)
{
	(void) argc;
	(void) argv;
	ft_printf("%s\n", ft_getenv("PWD", context->env.global));
	return (1);
}