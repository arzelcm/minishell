/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirections.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:57:53 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_REDIRECTIONS_H
# define TOKENIZER_REDIRECTIONS_H

# include "token.h"
# include "context.h"

void	free_redirections(t_redirection *list);

int		set_redirection(char *line, int *i, t_token *token);

char	*expand_redirect(t_redirection *redirection, t_context *context);

#endif