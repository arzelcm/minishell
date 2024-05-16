#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include <errno.h>

void	*safe_calloc(size_t size)
{
	void	*allocation;

	allocation = ft_calloc(1, size);
	if (!allocation)
		handle_syserror(ENOMEM);
	return (allocation);
}

void	safe_close(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}
