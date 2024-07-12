/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:10:20 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/12 19:38:02 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "family_helper.h"
#include "libft.h"

void	replace_last_token(t_token *parent, t_token *token)
{
	t_token	*aux;

	if (!parent)
		return ;
	aux = parent->tokens.token;
	while (aux && aux->next && aux->next->next)
		aux = aux->next;
	if (!parent->tokens.token || !parent->tokens.token->next)
		parent->tokens.token = token;
	else
		aux->next = token;
	token->parent = parent;
}

void
	push_first_child(t_token **current, t_token **parent, t_token *new_parent)
{
	t_token	*eval_token;
	t_token	*new_eval;

	eval_token = *current;
	new_eval = eval_token;
	while (new_eval->type != LIST
		&& new_eval->parent && new_eval->parent->type != SUBSHELL)
		new_eval = new_eval->parent;
	eval_token = new_eval;
	if (eval_token->parent && eval_token->parent->type < new_parent->type)
		replace_last_token(eval_token->parent, new_parent);
	push_token(new_parent, eval_token);
	if (*parent == NULL || (*parent == eval_token))
		*parent = new_parent;
}

int	set_list(char *line, int *i, t_token **parent, t_token **current)
{
	t_token	*new_parent;
	int		line_not_finish;
	int		is_and;
	int		is_or;

	line_not_finish = *i + 1 < (int) ft_strlen(line);
	is_and = line_not_finish && line[*i] == '&' && line[*i + 1] == '&';
	is_or = line_not_finish && line[*i] == '|' && line[*i + 1] == '|';
	if (!is_and && !is_or)
		return (0);
	new_parent = new_token(LIST);
	new_parent->dependency = AND;
	if (is_or)
		new_parent->dependency = OR;
	push_first_child(current, parent, new_parent);
	*current = new_token(CMD);
	push_token(new_parent, *current);
	(*i) += 2;
	return (1);
}

int	set_pipe(char *line, int *i, t_token **parent, t_token **current)
{
	t_token	*old_parent;
	t_token	*new_parent;

	if (line[*i] != '|')
		return (0);
	old_parent = (*current)->parent;
	if (!old_parent || old_parent->type != PIPE)
	{
		new_parent = new_token(PIPE);
		replace_last_token((*current)->parent, new_parent);
		(*current)->parent = new_parent;
		if (*parent == *current)
			*parent = (*current)->parent;
		push_token(new_parent, *current);
	}
	push_token((*current)->parent, new_token(CMD));
	*current = (*current)->next;
	if (*parent == NULL)
		*parent = (*current)->parent;
	(*i)++;
	return (1);
}

int	set_subshell(char *line, int *i, t_token **parent, t_token **current)
{
	t_token	*subshell;

	if (line[*i] == '(')
	{
		subshell = new_token(SUBSHELL);
		replace_last_token((*current)->parent, subshell);
		push_token(subshell, *current);
		if (!*parent)
			*parent = subshell;
	}
	else if (line[*i] == ')')
	{
		*current = (*current)->parent;
		while ((*current)->type != SUBSHELL && (*current)->parent)
			*current = (*current)->parent;
		if (*parent == (*current)->tokens.token)
			*parent = *current;
	}
	else
		return (0);
	(*i)++;
	return (1);
}

int	set_parent(char *line, int *i, t_token **parent, t_token **current)
{
	if (set_subshell(line, i, parent, current))
		return (1);
	else if (set_list(line, i, parent, current))
		return (1);
	else if (set_pipe(line, i, parent, current))
		return (1);
	else
		return (0);
}
