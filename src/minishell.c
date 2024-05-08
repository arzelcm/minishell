#include "libft.h"
#include "minishell.h"
#include "custom_utils.h"
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include "readline.h"
#include "history.h"

void	catch_sigint(int signal)
{
	struct termios	termios;

	if (signal != SIGINT)
		return ;
	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	ft_printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	listen_signals(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.__sigaction_u.__sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.__sigaction_u.__sa_handler = catch_sigint;
	sigaction(SIGINT, &sa, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void) argv;
	(void) envp;
	if (argc > 1)
		return (EXIT_FAILURE);
	listen_signals();
	ft_printf(CREDITS);
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
