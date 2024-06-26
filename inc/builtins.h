#ifndef BUILTINS_H
# define BUILTINS_H
# define PWD "pwd"
# define ENV "env"
# define ECHO "echo"
# define EXIT "exit"
# define EXPORT "export"
# define UNSET "unset"
# define CD "cd"
# define ABNORMAL_EXIT_STATUS 255

# include "pdata_helpers.h"

int		execute_builtin(char *command, t_token *token, t_context *context);

void	execute_cmd_builtin(t_pdata *pdata, t_token *token, t_context *context);

int		is_builtin(char *command);

int		ft_pwd(int argc, char **argv, t_context *context);

int		ft_env(int argc, char **argv, t_context *context);

int		ft_echo(int argc, char **argv, t_context *context);

int		ft_exit(int argc, char **argv, t_context *context);

int		ft_export(int argc, char **argv, t_context *context);

int		ft_unset(int argc, char **argv, t_context *context);

int		ft_cd(int argc, char **argv, t_context *context);

#endif