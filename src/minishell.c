#include "libft.h"
#include "context.h"
#include "minishell.h"
#include "utils.h"
#include "lexer.h"
#include "token.h"
#include "executor.h"
#include <stdlib.h>
#include <signal.h>
#include "signals.h"
#include "readline.h"
#include "history.h"
#include "expansor.h"
#include "tokenizer.h"
#include "environment.h"
#include "environment_helper.h"
#include "unistd.h"

int	g_sigval;

int	main(int argc, char **argv, char **envp)
{
	t_token		*token;
	t_context	context;
	char		*line;

	(void) argv;
	if (argc > 1)
	{
		ft_printff(STDERR_FILENO, "Args are not allowed.\n");
		return (EXIT_FAILURE);
	}
	g_sigval = 0;
	ft_bzero(&context, sizeof(t_context));
	ft_bzero(&token, sizeof(t_token *));
	init_env(&context, envp);
	if (isatty(STDIN_FILENO))
		ft_printf(CREDITS);
	while (42)
	{
		config_echoctl_terminal(OFF);
		listen_signals(MAIN, MAIN);
		if (isatty(STDIN_FILENO))
			line = readline(PROMPT);
		else
			line = get_next_line(STDIN_FILENO, 0);
		if (g_sigval == SIGINT)
		{
			context.err_code = 1;
			g_sigval = 0;
		}
		if (line == NULL)
			custom_exit(&context, 1);
		else if (*line)
		{
			add_history(line);
			if (check_syntax(&context, line))
			{
				token = tokenize(line, &context);
				execute(token, &context);
				free_token(token);
			}
		}
		free(line);
	}
	free_environment(&context.global_env);
	free_environment(&context.local_env);
	return (EXIT_SUCCESS);
}
