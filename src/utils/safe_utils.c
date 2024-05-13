#include "libft.h"
#include "minishell.h"
#include <errno.h>

void	*safe_calloc(size_t size)
{
	void	*allocation;

	allocation = ft_calloc(1, size);
	if (!allocation)
	{
		perror(PROGRAM_NAME);
		exit(ENOMEM);
	}
	return (allocation);
}
