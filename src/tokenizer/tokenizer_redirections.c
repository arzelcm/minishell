/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:27 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/16 19:18:21 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "token.h"
#include "tokenizer.h"
#include "tokenizer_utils.h"
#include "tokenizer_redirections.h"
#include "safe_utils.h"
#include "words.h"
#include <stdlib.h>

void	free_redirections(t_redirection *list)
{
	t_redirection	*aux;

	while (list)
	{
		aux = list;
		list = list->next;
		free(aux->path);
		free(aux);
	}
}

t_redirection	*new_redirection(t_redirection_mode mode, char *path)
{
	t_redirection	*redirection;

	redirection = safe_calloc(sizeof(t_redirection));
	redirection->mode = mode;
	redirection->path = path;
	return (redirection);
}

void
	push_redirection(t_redirection_mode mode, char *path, t_token *token)
{
	t_redirection	*current;

	if (!path || mode == UNKNOWN_RED)
		return ;
	if (mode == HERE_DOC)
		token->here_docs++;
	if (mode == HERE_DOC || mode == INPUT)
		token->infiles++;
	else
		token->outfiles++;
	if (!token->redirections)
	{
		token->redirections = new_redirection(mode, path);
		return ;
	}
	current = token->redirections;
	while (current->next)
		current = current->next;
	current->next = new_redirection(mode, path);
}

int	set_redirection(char *line, int *i, t_token *token)
{
	t_redirection_mode	mode;

	mode = UNKNOWN_RED;
	if (line[*i] == '<' && line[*i + 1] == '<')
		mode = HERE_DOC;
	else if (line[*i] == '<')
		mode = INPUT;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		mode = APPEND;
	else if (line[*i] == '>')
		mode = OUTPUT;
	if (mode == HERE_DOC || mode == APPEND)
		(*i) += 2;
	else if (mode == INPUT || mode == OUTPUT)
		(*i)++;
	if (mode != UNKNOWN_RED)
		push_redirection(mode, get_raw_word(line, i), token);
	return (mode != UNKNOWN_RED);
}

char	*expand_redirect(t_redirection *red, t_context *context)
{
	t_words		words;
	t_words		src;
	int			i;

	init_words(&words);
	init_words(&src);
	i = 0;
	avoid_spaces(red->path, &i);
	push_arg(&src.body, safe_ft_strdup(red->path + i, syserr), &src.count);
	set_words(&words, src.body, context);
	free_matrix(src.body);
	if (!set_redirection_path(red, &words, context, &i))
		return (NULL);
	return (red->path);
}
