/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:41 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/09 15:43:38 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	use_line(char *line, t_token *token, t_context *context)
{
	add_history(line);
	if (check_syntax(context, line))
	{
		token = tokenize(line);
		execute(token, context);
		free_token(token);
	}
}

void	infinite_prompt(char *line, t_token *token, t_context *context)
{
	while (42)
	{
		config_echoctl_terminal(OFF);
		listen_signals(MAIN, MAIN);
		if (isatty(STDIN_FILENO) || FORCE_PROMPT)
			line = readline(PROMPT);
		else
			line = get_next_line(STDIN_FILENO, 0);
		if (g_sigval == SIGINT)
		{
			context->err_code = 1;
			g_sigval = 0;
		}
		if (!line)
			custom_exit(context, 1);
		else if (*line)
			use_line(line, token, context);
		free(line);
	}
}

void	init(t_context *context, char **line, t_token **token, char **envp)
{
	(void) context;
	g_sigval = 0;
	*line = NULL;
	*token = NULL;
	ft_bzero(context, sizeof(t_context));
	init_env(context, envp);
}

void	clean(t_context *context)
{
	free_environment(&context->global_env);
	free_environment(&context->local_env);
}

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
	init(&context, &line, &token, envp);
	if (isatty(STDIN_FILENO))
		ft_printf(CREDITS);
	infinite_prompt(line, token, &context);
	clean(&context);
	return (EXIT_SUCCESS);
}
