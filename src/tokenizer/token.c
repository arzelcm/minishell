#include "libft.h"
#include "token.h"
#include "tokenizer.h"
#include "tokenizer_redirections.h"
#include "safe_utils.h"

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
	if (!token)
		return ;
	free_redirections(token->redirections);
	free_tokens(&token->tokens);
	free_args(token->args);
	free(token);
}

t_token	*new_token(t_token_type type)
{
	t_token	*token;

	token = safe_calloc(sizeof(t_token));
	token->type = type;
	token->tokens.amount = 1;
	return (token);
}

void	print_token(t_token *token)
{
	t_redirection	*aux;
	int				i;

	ft_printf("token %p\n", token);
	if (!token)
		return ;
	ft_printf("type: %i\n", token->type);
	ft_printf("argc: %i\n", token->argc);
	ft_printf("args: ");
	i = 0;
	while (token->args && token->args[i])
	{
		ft_printf("%s, ", token->args[i]);
		i++;
	}
	ft_printf("\nredirections: ");
	aux = token->redirections;
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
		ft_printf("\nChild %i\n", i);
		print_token(aux_tok);
		i++;
		aux_tok = aux_tok->next;
	}
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
