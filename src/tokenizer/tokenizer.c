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
	if (*token == *actual)
	{
		*token = new_token(PIPE);
		push_token(&(*token)->tokens, *actual);
	}
	*actual = new_token(CMD);
	push_token(&(*token)->tokens, *actual);
	return (1);
}

int	set_definitions(char *line, int *i, t_context *context, t_token **token)
{
	char	*key;
	char	*value;
	char	*aux;
	int		aux_i;

	aux_i = 0;
	if (line[*i] != '=')
		return (0);
	key = ft_substr(line, 0, *i);
	aux = ft_substr(line, *i + 1, -1);
	value = get_word(aux, &aux_i, context);
	free(aux);
	ft_putenv(key, value, &context->env);
	free(key);
	free(value);
	free_token(*token);
	*token = NULL;
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
	while (line[i] && token)
	{
		// TODO: Get word?
		if (avoid_spaces(line, &i))
			continue ;
		if (set_definitions(line, &i, context, &token))
			continue ;
		if (set_redirection(line, &i, actual, context))
			continue ;
		if (set_pipe(line, &i, &token, &actual))
			continue ;
		push_arg(&actual->args, get_word(line, &i, context), &token->argc);
	}
	// print_token(token);
	return (token);
}
