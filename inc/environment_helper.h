#ifndef ENVIROMENT_HELPER_H
# define ENVIROMENT_HELPER_H

# include "environment.h"

void	increase_var(char *key, t_env *env);

void	print_env(t_env *env);

void	free_enviroment(t_env *env);

#endif