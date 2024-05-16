#include "libft.h"
#include "safe_utils.h"
#include "token.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include "tokenizer_utils.h"
#include "tokenizer_redirections.h"

void	free_args(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
}

void	free_token(t_token *token);

void	free_tokens(t_tokens *tokens)
{
	t_token	*aux;

	while (tokens->token)
	{
		aux = tokens->token;
		tokens->token = tokens->token->next;
		free_token(aux);
	}
}

void	free_token(t_token *token)
{
	free_redirections(token->infiles);
	free_redirections(token->outfiles);
	free_tokens(&token->tokens);
	free_args(token->args);
	free(token);
}

t_token	*new_token(t_token_type type)
{
	t_token	*token;

	token = safe_calloc(sizeof(t_token));
	token->type = type;
	return (token);
}

void	print_token(t_token *token)
{
	t_redirection	*aux;
	int				i;
	ft_printf("token %p (%i)\n", token, token->type);
	ft_printf("args: ", token, token->type);
	i = 0;
	while (token->args && token->args[i])
	{
		ft_printf("%s, ", token->args[i]);
		i++;
	}
	ft_printf("\ninfiles: ");
	aux = token->infiles;
	while (aux)
	{
		ft_printf("%s(%i), ", aux->path, aux->mode);
		aux = aux->next;
	}
	ft_printf("\noutfiles: ");
	aux = token->outfiles;
	while (aux)
	{
		ft_printf("%s(%i), ", aux->path, aux->mode);
		aux = aux->next;
	}
	ft_printf("\nhere_docs: %i\n", token->here_docs);
	ft_printf("tokens: %i\n", token->tokens.amount);
	t_token *aux_tok = token->tokens.token;
	i = 0;
	while (aux_tok)
	{
		ft_printf("\nChild token %i\n", i);
		print_token(aux_tok);
		i++;
		aux_tok = aux_tok->next;
	}
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

void	push_token(t_tokens *tokens, t_token *token)
{
	t_token	*aux;

	aux = tokens->token;
	if (!aux)
	{
		tokens->token = token;
		tokens->amount = 1;
	}
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = token;
		tokens->amount++;
	}
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

t_token	*tokenize(char *line)
{
	t_token			*token;
	t_token			*actual;
	int				i;

	token = new_token(CMD);
	actual = token;
	i = 0;
	while (line[i])
	{
		avoid_spaces(line, &i);
		if (set_redirection(line, &i, actual))
			continue ;
		if (set_pipe(line, &i, &token, &actual))
			continue ;
		push_arg(&actual->args, get_word(line, &i));
	}
	print_token(token);
	return (token);
}
