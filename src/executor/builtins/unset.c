#include "context.h"
#include "environment.h"

int	ft_unset(int argc, char **argv, t_context *context)
{
	int	i;

	i = 1;
	while (i < argc && argv[i])
	{
		if(!ft_deleteenv(argv[i], &context->local_env))
			ft_deleteenv(argv[i], &context->global_env);
		i++;
	}
	return (1);
}