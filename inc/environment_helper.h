#ifndef ENVIRONMENT_HELPER_H
# define ENVIRONMENT_HELPER_H

# include "environment.h"

void	increase_var(char *key, t_context *context);

void	print_env(char **env);

void	free_enviroment(t_env *env);

void	copy_envp(char **dst, char **src, int duplicate);

#endif