#ifndef EXPANSOR_H
# define EXPANSOR_H

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

void	expanse(char **line);

#endif