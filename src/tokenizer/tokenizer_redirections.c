/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:27 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:59:27 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "token.h"
#include "tokenizer_utils.h"
#include "safe_utils.h"
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

char	*expand_redirect(t_redirection *redirection, t_context *context)
{
	t_expansion	expansion;
	char		*word;
	int			i;

	i = 0;
	avoid_spaces(redirection->path, &i);
	if (redirection->mode == HERE_DOC)
		word = get_raw_word(redirection->path, &i);
	else
		word = get_word(redirection->path, &i, context, &expansion);
	if (expansion.expanded && !expansion.quoted
		&& (ft_stroccurrences_set(word, " \t") || !*word))
	{
		handle_error(redirection->path, "ambiguous redirect");
		context->err_code = EXIT_FAILURE;
		free(word);
		return (NULL);
	}
	free(redirection->path);
	redirection->path = word;
	return (redirection->path);
}
