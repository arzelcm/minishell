#include "libft.h"
#include "minishell.h"

void	custom_exit(int exit_code)
{
	ft_printf("exit\n");
	exit(exit_code);
}