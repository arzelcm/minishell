/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:31 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/10 00:03:35 by arcanava         ###   ########.fr       */
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

int	set_pipe(char *line, int *i, t_token **token, t_token **actual)
{
	if (line[*i] != '|')
		return (0);
	(*i)++;
	if (!*token)
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
	t_token			*curr_token;
	int				i;

	token = NULL;
	curr_token = NULL;
	i = 0;
	while (line[i])
	{
		if (avoid_spaces(line, &i))
			continue ;
		if (!curr_token)
			curr_token = new_token(CMD);
		if (set_redirection(line, &i, curr_token))
			continue ;
		if (set_pipe(line, &i, &token, &curr_token))
			continue ;
		push_arg(&curr_token->args, get_raw_word(line, &i), &curr_token->argc);
	}
	if (!token)
		token = curr_token;
	return (token);
}

int	avoid_spaces(char *str, int *i)
{
	if (str[*i] != ' ' && str[*i] != '\t')
		return (0);
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	return (1);
}
