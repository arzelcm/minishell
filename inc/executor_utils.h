#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "pdata_helpers.h"
# include <stdlib.h>

int		wait_child_processes(pid_t last_pid, int cmds_amount);

void	close_pipe(int fds[2]);

void	redirect_fds(int read_fd, int write_fd);

void	clean_exit(t_pdata *pdata);

#endif
