/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:01 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:58:01 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "token.h"
# include "context.h"

t_token	*tokenize(char *line);

void	free_args(char **args);

int		set_definitions(char *line, int *i,
			t_context *context, t_token **token);

void	push_arg(char ***args, char *new_arg, int *argc);

#endif