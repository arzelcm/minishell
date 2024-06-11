#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "context.h"
# include "token.h"
# include <stdlib.h>

int		wait_child_processes(pid_t last_pid, int cmds_amount);

void	close_pipe(int fds[2]);

#endif
