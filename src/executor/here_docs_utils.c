/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:01:40 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/07/15 18:35:22 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "context.h"
#include "open.h"
#include "safe_utils.h"
#include <signal.h>

static void	recursive_close(t_token *token)
{
	t_token	*curr_token;

	if (token->tokens.token && token->tokens.token)
		recursive_close(token->tokens.token);
	if (token->tokens.token)
		curr_token = token->tokens.token->next;
	while (token->tokens.token && curr_token)
	{
		recursive_close(curr_token);
		curr_token = curr_token->next;
	}
	safe_close(&token->here_doc_fd);
}

void	close_here_docs(t_token *token)
{
	t_token	*absolute_parent;

	absolute_parent = token;
	while (absolute_parent->parent)
		absolute_parent = absolute_parent->parent;
	recursive_close(absolute_parent);
}

static void	recursive_open(t_token *token)
{
	t_token	*curr_token;

	if (g_sigval == SIGINT)
		return ;
	if (token->tokens.token && token->tokens.token)
		recursive_open(token->tokens.token);
	if (token->tokens.token)
		curr_token = token->tokens.token->next;
	while (token->tokens.token && curr_token)
	{
		recursive_open(curr_token);
		curr_token = curr_token->next;
	}
	token->here_doc_fd = open_here_docs(token->redirections, token->here_docs);
}

void	initialize_heredocs(t_token *token)
{
	recursive_open(token);
	if (g_sigval == SIGINT)
		close_here_docs(token);
}
