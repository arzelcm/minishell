#ifndef EXPANSOR_H
# define EXPANSOR_H
# include "context.h"

typedef struct s_expansion
{
	int	expanded;
	int	quoted;
}	t_expansion;

int	expand(char **line, t_context *context, t_expansion *expansion);

int	variable_finished(char c, int not_first);

#endif