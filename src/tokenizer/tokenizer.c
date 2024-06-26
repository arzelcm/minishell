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
	int		i;

	new = safe_calloc(sizeof(char *) * (*argc + 2));
	i = -1;
	while (++i < *argc)
		new[i] = (*args)[i];
	new[*argc] = new_arg;
	new[*argc + 1] = NULL;
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

void	set_arg(char *line, int *i, t_token *token, t_context *context)
{
	char	**words;
	char	*word;
	int		j;
	int		expanded;
	int		quoted;

	expanded = 0;
	quoted = 0;
	word = get_word(line, i, context, &expanded, &quoted);
	if (!expanded || quoted)
		push_arg(&token->args, word, &token->argc);
	else
	{
		words = ft_split(word, ' ');
		j = 0;
		while (words[j])
			push_arg(&token->args, words[j++], &token->argc);
		free(words);
		free(word);
	}
}

static void	checks(t_token **token)
{
	int	delete;

	delete = (*token)->type == CMD && (*token)->argc == 0;
	if (delete)
	{
		free_token(*token);
		*token = NULL;
	}
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
		set_arg(line, &i, curr_token, context);
		checks(&curr_token);
	}
	if (!token)
		token = curr_token;
	return (token);
}
