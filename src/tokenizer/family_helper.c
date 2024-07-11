/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:10:20 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/11 16:12:06 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "family_helper.h"
#include "libft.h"

void	replace_last_token(t_token *parent, t_token *token)
{
	t_token	*aux;

	aux = parent->tokens.token;
	while (aux && aux->next && aux->next->next)
		aux = aux->next;
	aux->next = token;
	token->parent = parent;
}

void	create_parent(t_token **current, t_token *new_parent, t_token **parent)
{
	t_token	*old_parent;

	old_parent = (*current)->parent;
	if (old_parent)
	{
		if (old_parent->type >= new_parent->type)
			replace_last_token(old_parent, new_parent);
		else if (old_parent->type < new_parent->type)
		{
			if (old_parent->parent)
				replace_last_token(old_parent->parent, new_parent);
			push_token(new_parent, old_parent);
			if (*parent == old_parent)
				*parent = new_parent;
		}
	}
	else if (*parent == NULL || new_parent->type > (*parent)->type)
		*parent = new_parent;
	if (!old_parent || old_parent->type >= new_parent->type)
		push_token(new_parent, *current);
	*current = new_token(CMD);
	push_token(new_parent, *current);
}

int	set_list(char *line, int *i, t_token **parent, t_token **current)
{
	int		is_and;
	int		is_or;
	int		line_len;
	t_token	*list;

	(void) current;
	line_len = ft_strlen(line);
	is_and = *i + 1 < line_len && line[*i] == '&' && line[*i + 1] == '&';
	is_or = *i + 1 < line_len && !is_and
		&& line[*i] == '|' && line[*i + 1] == '|';
	if (is_and || is_or)
	{
		list = new_token(LIST);
		list->dependency = AND;
		if (is_or)
			list->dependency = OR;
		create_parent(current, new_token(LIST), parent);
		(*i) += 2;
		return (1);
	}
	else
		return (0);
}

int	set_pipe(char *line, int *i, t_token **parent, t_token **current)
{
	if (line[*i] != '|')
		return (0);
	if ((*current)->parent && (*current)->parent->type == PIPE)
	{
		push_token((*current)->parent, new_token(CMD));
		*current = (*current)->next;
	}
	else
		create_parent(current, new_token(PIPE), parent);
	(*i)++;
	return (1);
}

int	set_parent(char *line, int *i, t_token **parent, t_token **current)
{
	if (set_list(line, i, parent, current))
		return (1);
	else if (set_list(line, i, parent, current))
		return (1);
	else if (set_pipe(line, i, parent, current))
		return (1);
	else
		return (0);
}
