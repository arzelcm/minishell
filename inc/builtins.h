#ifndef BUILTINS_H
# define BUILTINS_H
# define PWD "pwd"
# define ENV "env"
# define ECHO "echo"
# define EXIT "exit"
# define EXPORT "export"

# include "context.h"

int	ft_pwd(int argc, char **argv, t_context *context);

int	ft_env(int argc, char **argv, t_context *context);

int	ft_echo(int argc, char **argv, t_context *context);

int	ft_exit(int argc, char **argv, t_context *context);

int	ft_export(int argc, char **argv, t_context *context);

#endif