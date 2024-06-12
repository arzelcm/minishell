#include "libft.h"
#include "safe_utils.h"
#include "token.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include "tokenizer_utils.h"
#include "tokenizer_redirections.h"
#include "token.h"
#include "builtins.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
}

void	push_arg(char ***args, char *new_arg, int *argc)
{
	char	**new;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (*args && (*args)[i])
		i++;
	len = i;
	new = safe_calloc(sizeof(char *) * (len + 2));
	i = -1;
	while (++i < len)
		new[i] = (*args)[i];
	new[len] = new_arg;
	new[len + 1] = NULL;
	free(*args);
	*args = new;
	(*argc)++;
}

int	set_pipe(char *line, int *i, t_token **token, t_token **actual)
{
	if (line[*i] != '|')
		return (0);
	(*i)++;
	if (!*token)
	{
		*token = new_token(PIPE);
		push_token(&(*token)->tokens, *actual);
	}
	*actual = new_token(CMD);
	push_token(&(*token)->tokens, *actual);
	return (1);
}

t_token	*tokenize(char *line, t_context *context)
{
	t_token			*token;
	t_token			*curr_token;
	int				i;

	token = NULL;
	curr_token = NULL;
	i = 0;
	while (line[i])
	{
		if (avoid_spaces(line, &i))
			continue ;
		if (!curr_token)
			curr_token = new_token(CMD);
		if (set_redirection(line, &i, curr_token, context))
			continue ;
		if (set_pipe(line, &i, &token, &curr_token))
			continue ;
		push_arg(&curr_token->args, get_word(line, &i, context), &curr_token->argc);
	}
	if (!token)
		token = curr_token;
	print_token(token);
	return (token);
}
