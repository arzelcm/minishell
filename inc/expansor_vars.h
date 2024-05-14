#ifndef EXPANSOR_VARS_H
# define EXPANSOR_VARS_H
# define VAR_LIMIT "\"'|<><<>> "

# include "context.h" 

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

void	fill_needed_vars(t_vars *vars, char *line, t_context *context);

void	free_expansor_vars(t_var *var);

t_var	*get_var(char *key, t_vars *vars, t_context *context);

#endif