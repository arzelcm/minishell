/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/11 15:31:13 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "context.h"

typedef enum e_token_type
{
	CMD,
	PIPE,
	SUBSHELL,
	LIST
}	t_token_type;

typedef enum e_redirection_mode
{
	HERE_DOC,
	INPUT,
	OUTPUT,
	APPEND,
	UNKNOWN_RED
}	t_redirection_mode;

typedef enum e_dependency
{
	AND,
	OR
}	t_dependency;

typedef struct s_redirection
{
	union
	{
		char	*path;
		char	*delimiter;
	};
	t_redirection_mode		mode;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_token	t_token;

typedef struct s_tokens
{
	t_token	*token;
	int		amount;
}	t_tokens;

typedef struct s_token
{
	t_token_type	type;
	char			*raw_token;
	char			**args;
	int				expanded;
	int				argc;
	t_redirection	*redirections;
	int				here_docs;
	int				infiles;
	int				outfiles;
	t_dependency	dependency;
	t_token			*parent;
	t_token			*next;
	t_tokens		tokens;
}	t_token;

void	free_token(t_token *token);

t_token	*new_token(t_token_type type);

void	print_token(t_token *token);

void	push_token(t_token *parent, t_token *token);

void	expand_args(t_token *token, t_context *context);

#endif
