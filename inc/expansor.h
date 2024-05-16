#ifndef EXPANSOR_H
# define EXPANSOR_H
# include "context.h"

int	expand(char **line, t_context *context);

int		variable_finished(char c, int not_first);

void	init_expansor_vars(t_context *context);

#endif