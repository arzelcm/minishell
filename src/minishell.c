#include "libft.h"
#include "minishell.h"
#include "custom_utils.h"
#include <stdlib.h>
#include "readline.h"
#include "history.h"

void	new_line(int key)
{
	(void) key;
	ft_printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	prevent(int key)
{
	(void) key;
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	listen_signals(void)
{
	signal(SIGINT, new_line);
	signal(SIGQUIT, prevent);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void) argv;
	(void) envp;
	if (argc > 1)
		return (EXIT_FAILURE);
	listen_signals();
	ft_printf("\n");
	while (42)
	{
		line = readline(PROMPT);
		if (line && *line)
			add_history(line);
		else if (line == NULL)
			custom_exit(EXIT_SUCCESS);
		free(line);
	}
	return (EXIT_SUCCESS);
}
