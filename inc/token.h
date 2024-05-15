#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	CMD,
	PIPE
}	t_token_type;

typedef enum e_redirection_mode
{
	INPUT,
	OUTPUT,
	HERE_DOC,
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
	t_redirection	*infiles;
	t_redirection	*outfiles;
	t_redirection	*here_docs;
	t_tokens		*tokens;
}	t_token;

#endif
