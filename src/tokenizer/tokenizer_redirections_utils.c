/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirections_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:14 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/16 19:21:57 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "tokenizer_redirections.h"
#include "words.h"
#include "stdlib.h"
#include "tokenizer_utils.h"
#include "utils.h"

int	set_redirection_path(t_redirection *red, t_words *words,
	t_context *context, int *i)
{
	char	*word;

	if (red->mode == HERE_DOC)
		word = get_raw_word(red->path, i);
	else if (words->count != 1)
	{
		handle_error(red->path, "ambiguous redirect");
		context->err_code = EXIT_FAILURE;
		free_matrix(words->body);
		return (0);
	}
	else
	{
		word = safe_ft_strdup(words->body[0], syserr);
		free_matrix(words->body);
	}
	free(red->path);
	red->path = word;
	return (1);
}
