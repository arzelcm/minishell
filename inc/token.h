#ifndef TOKEN_H
# define TOKEN_H

typedef union u_redirection_arg	t_redirection_arg;
typedef enum e_token_types		t_token_types;
typedef enum e_redirection_mode	t_redirection_mode;
typedef struct s_tokens			t_tokens;
typedef struct s_token			t_token;
typedef struct s_redirection	t_redirection;

enum e_token_types
{
	CMD
};

enum e_redirection_mode
{
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND
};

struct s_redirection
{
	union
	{
		char			*path;
		char			*delimiter;
	};
	t_redirection_mode	mode;
	t_redirection		*next;
};

struct s_tokens
{
	t_token	*token;
	int		amount;
};

struct s_token
{
	t_token_types	type;
	char			*raw_token;
	char			**args;
	t_redirection	*infiles;
	t_redirection	*outfiles;
	t_redirection	*here_docs;
	t_tokens		*tokens;
};

#endif
