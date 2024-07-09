/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:24 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/09 01:40:32 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "tokenizer.h"
#include "tokenizer_redirections.h"
#include "safe_utils.h"
#include "tokenizer_utils.h"
#include "utils.h"

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

// 	ft_printf("token %p\n", token);
// 	if (!token)
// 		return ;
// 	ft_printf("type: %i\n", token->type);
// 	ft_printf("argc: %i\n", token->argc);
// 	ft_printf("expanded: %i\n", token->expanded);
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
// 	ft_printf("\nhere_docs: %i\n", token->here_docs);
// 	ft_printf("tokens: %i\n", token->tokens.amount);
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

void	split_push(char ***new_args, char *word, int *argc)
{
	char		**words;
	int			j;

	words = safe_ft_split_set(word, " \t", handle_syserror);
	j = 0;
	while (words[j])
	{
		push_arg(new_args, words[j], argc);
		j++;
	}
	free(words);
	free(word);
}

void	expand_args(t_token *token, t_context *context)
{
	t_expansion	expansion;
	char		**new_args;
	char		*word;
	int			i;
	int			j;
	int			k;
	int			create_new_arg;

	if (token->expanded)
		return ;
	new_args = NULL;
	token->argc = 0;
	i = 0;
	while (token->args && token->args[i])
	{
		j = 0;
		create_new_arg = 1;
		while (token->args[i][j])
		{
			word = get_word(token->args[i], &j, context, &expansion);
			if (expansion.expanded && !expansion.quoted && !*word)
			{
				free(word);
				continue ;
			}
			k = 0;
			while (k < (int) ft_strlen(word) || k == 0)
			{
				if (create_new_arg)
				{
					push_arg(&new_args,
						safe_ft_strdup("", handle_syserror), &token->argc);
					create_new_arg = 0;
				}
				if (expansion.expanded && !expansion.quoted
					&& ft_stroccurrences(" \t", word[k]))
				{
					create_new_arg = !new_args
						|| ft_strlen(new_args[token->argc - 1]) > 0;
					avoid_spaces(word, &k);
				}
				else
					push_char(new_args + token->argc - 1, word[k++]);
			}
			free(word);
		}
		i++;
	}
	token->expanded = 1;
	free_args(token->args);
	token->args = new_args;
}
