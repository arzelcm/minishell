#include "libft.h"
#include "context.h"
#include "minishell.h"
#include "utils.h"
#include "lexer.h"
#include "token.h"
#include "executor.h"
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include "readline.h"
#include "history.h"
#include "expansor.h"

static void	catch_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	listen_signals(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.__sigaction_u.__sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.__sigaction_u.__sa_handler = catch_sigint;
	sigaction(SIGINT, &sa, NULL);
}

static void	config_terminal(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

int	main(int argc, char **argv, char **envp)
{
	t_context	context;
	t_token		token;
	char		*line;

	(void) argv;
	(void) envp;
	if (argc > 1)
		return (EXIT_FAILURE);
	ft_bzero(&context, sizeof(t_context));
	ft_bzero(&token, sizeof(t_token));
	config_terminal();
	listen_signals();
	ft_printf(CREDITS);
	while (42)
	{
		line = readline(PROMPT);
		if (line == NULL)
			custom_exit(EXIT_SUCCESS);
		else if (*line)
		{
			add_history(line);
			if (check_syntax(&context, line))
			{
				expand(&line, &context);
				// tokenize(line, context);
				execute(line, &token, &context);
			}
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
