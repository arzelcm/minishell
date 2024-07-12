/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:31 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/11 15:05:56 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "safe_utils.h"
#include "token.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include "tokenizer_utils.h"
#include "tokenizer_redirections.h"
#include "token.h"
#include "builtins.h"
#include "family_helper.h"

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

t_token	*tokenize(char *line)
{
	t_token			*parent;
	t_token			*current;
	int				i;

	parent = NULL;
	current = NULL;
	i = 0;
	while (line[i])
	{
		if (avoid_spaces(line, &i))
			continue ;
		if (!current)
			current = new_token(CMD);
		if (set_redirection(line, &i, current))
			continue ;
		if (set_parent(line, &i, &parent, &current))
			continue ;
		push_arg(&current->args, get_raw_word(line, &i), &current->argc);
	}
	if (!parent)
		parent = current;
	return (parent);
}

int	avoid_spaces(char *str, int *i)
{
	if (str[*i] != ' ' && str[*i] != '\t')
		return (0);
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	return (1);
}
