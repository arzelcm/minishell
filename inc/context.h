#ifndef CONTEXT_H
# define CONTEXT_H
# define SYNTAX_ERROR 258

typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_vars
{
	int		size;
	int		keys_length;
	int		values_length;
	t_var	*list;
}	t_vars;

typedef struct s_context
{
	int		err_code;
	t_vars	*vars;
}	t_context;

#endif
