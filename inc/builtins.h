#ifndef BUILTINS_H
# define BUILTINS_H
# define PWD "pwd"
# define ENV "env"

# include "context.h"

int	ft_pwd(int argc, char **argv, t_context *context);

int	ft_env(int argc, char **argv, t_context *context);

#endif