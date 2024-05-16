#include "libft.h"
#include "minishell.h"

void	custom_exit(int exit_code)
{
	ft_printff(STDERR_FILENO, "\033[1A%sexit\n", PROMPT);
	exit(exit_code);
}
