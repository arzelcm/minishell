#ifndef EXPANSOR_H
# define EXPANSOR_H

typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
	int				occurrences;
}	t_var;

typedef struct s_vars
{
	int		size;
	t_var	*list;
}	t_vars;

void	expanse(char **line);

#endif