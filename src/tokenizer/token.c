/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:24 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/11 15:12:32 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "tokenizer.h"
#include "tokenizer_redirections.h"
#include "safe_utils.h"
#include "tokenizer_utils.h"
#include "utils.h"
#include "words.h"

void	free_token(t_token *token)
{
	t_token	*aux;

	if (!token)
		return ;
	free_redirections(token->redirections);
	while (token->tokens.token)
	{
		aux = token->tokens.token;
		token->tokens.token = token->tokens.token->next;
		free_token(aux);
	}
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

// void	print_token(t_token *token)
// {
// 	t_redirection	*aux;
// 	int				i;

// 	ft_printf("token \n", token);
// 	if (!token)
// 		return ;
// 	ft_printf("type: %i\n", token->type);
// 	ft_printf("argc: %i\n", token->argc);
// 	// ft_printf("expanded: %i\n", token->expanded);
// 	ft_printf("args: ");
// 	i = 0;
// 	while (token->args && token->args[i])
// 	{
// 		ft_printf("%s, ", token->args[i]);
// 		i++;
// 	}
// 	ft_printf("\nredirections: ");
// 	aux = token->redirections;
// 	while (aux)
// 	{
// 		ft_printf("%s(%i), ", aux->path, aux->mode);
// 		aux = aux->next;
// 	}
// 	// ft_printf("\nhere_docs: %i\n", token->here_docs);
// 	ft_printf("\ntokens: %i\n", token->tokens.amount);
// 	t_token *aux_tok = token->tokens.token;
// 	i = 0;
// 	while (aux_tok)
// 	{
// 		ft_printf("\nChild %i\n", i);
// 		print_token(aux_tok);
// 		i++;
// 		aux_tok = aux_tok->next;
// 	}
// }

void	push_token(t_token *parent, t_token *token)
{
	t_token	*aux;

	token->parent = parent;
	aux = parent->tokens.token;
	if (!aux)
	{
		parent->tokens.token = token;
		parent->tokens.amount = 1;
	}
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = token;
		parent->tokens.amount++;
	}
}

void	expand_args(t_token *token, t_context *context)
{
	t_words		words;

	if (token->expanded)
		return ;
	words.body = NULL;
	words.count = 0;
	set_words(&words, token->args, context);
	token->expanded = 1;
	free_args(token->args);
	token->argc = words.count;
	token->args = words.body;
}
