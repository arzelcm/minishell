#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "context.h"

int		wait_child_processes(pid_t last_pid, int cmds_amount);

int		is_a_builtin(char *command, t_token *token, t_context *context);

void	close_pipe(int fds[2]);

int		open_infile(char *path);

int		open_outfile(char *path, int mode);

#endif
