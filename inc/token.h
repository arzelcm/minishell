#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	CMD,
	PIPE,
	DEFINITION
}	t_token_type;

typedef enum e_redirection_mode
{
	HERE_DOC,
	INPUT,
	OUTPUT,
	APPEND
}	t_redirection_mode;

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
	int				argc;
	t_redirection	*infiles;
	t_redirection	*outfiles;
	int				here_docs;
	t_token			*next;
	t_tokens		tokens;
}	t_token;

void	free_token(t_token *token);

t_token	*new_token(t_token_type type);

void	print_token(t_token *token);

void	push_token(t_tokens *tokens, t_token *token);

#endif
