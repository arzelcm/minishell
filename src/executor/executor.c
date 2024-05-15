#include "libft.h"
#include "executor.h"

void	execute(char *line, t_token *token, t_context *context)
{
	ft_printf("Executing:\n%s\n", line, token, context);
}