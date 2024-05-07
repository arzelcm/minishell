#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	char	*curr_line;

	(void) argv;
	(void) envp;
	if (argc > 1)
		return (EXIT_FAILURE);
	ft_printf("\n");
	while (42)
	{
		curr_line = readline(PROMPT);
		free(curr_line);
	}
	return (EXIT_SUCCESS);
}
