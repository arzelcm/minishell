#ifndef EXPANSOR_VARS_H
# define EXPANSOR_VARS_H

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

void	fill_needed_vars(t_vars *vars, char *line);

void	free_expansor_vars(t_var *var);

t_var	*get_var(char *key, t_vars *vars);

#endif