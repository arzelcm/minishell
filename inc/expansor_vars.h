#ifndef EXPANSOR_VARS_H
# define EXPANSOR_VARS_H
# define VAR_LIMIT "\"'|<><<>> "

# include "context.h"

void	fill_needed_vars(char *line, t_context *context);

void	free_expansor_vars(t_vars **vars);

t_var	*get_var(char *key, t_context *context);

#endif