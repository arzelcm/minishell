#include "libft.h"
#include "safe_utils.h"
#include "token.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include "tokenizer_utils.h"
#include "tokenizer_redirections.h"
#include "token.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
}

void	push_arg(char ***args, char *new_arg)
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
}

int	set_pipe(char *line, int *i, t_token **token, t_token **actual)
{
	if (line[*i] != '|')
		return (0);
	(*i)++;
	if (*token == *actual)
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
	t_token			*actual;
	int				i;

	token = new_token(CMD);
	actual = token;
	i = 0;
	while (line[i])
	{
		if (avoid_spaces(line, &i))
			continue ;
		if (set_redirection(line, &i, actual, context))
			continue ;
		if (set_pipe(line, &i, &token, &actual))
			continue ;
		push_arg(&actual->args, get_word(line, &i, context));
	}
	// print_token(token);
	return (token);
}
