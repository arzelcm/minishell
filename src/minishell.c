#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void) argv;
	(void) envp;
	if (argc > 1)
		return (EXIT_FAILURE);
	ft_printf("\n");
	while (42)
	{
		line = readline(PROMPT);
		if (line && *line)
			add_history(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
