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

int	main(int argc, char **argv, char **envp)
{
	t_token		*token;
	t_context	context;
	char		*line;

	(void) argv;
	if (argc > 1)
		return (EXIT_FAILURE);
	g_sigval = 0;
	ft_bzero(&context, sizeof(t_context));
	ft_bzero(&token, sizeof(t_token*));
	init_env(&context.global_env, &context.local_env, envp);
	ft_printf(CREDITS);
	while (42)
	{
		config_echoctl_terminal(OFF);
		listen_signals(MAIN, MAIN);
		line = readline(PROMPT);
		if (g_sigval == SIGINT)
		{
			context.err_code = 1;
			g_sigval = 0;
		}
		if (line == NULL)
			custom_exit(EXIT_SUCCESS);
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
	free_enviroment(&context.global_env);
	free_enviroment(&context.local_env);
	return (EXIT_SUCCESS);
}
