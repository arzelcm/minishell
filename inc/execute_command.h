#ifndef EXECUTE_COMMAND_H
# define EXECUTE_COMMAND_H

# define DEF_PATH "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"

void	execute_by_path(char **args, char **envp);

#endif
