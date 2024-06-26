#include "libft.h"
#include "open.h"
#include "safe_utils.h"
#include "utils.h"
#include "pdata_helpers.h"
#include <errno.h>
#include <sys/wait.h>

int	wait_child_processes(pid_t last_pid, int cmds_amount)
{
	pid_t	pid;
	int		tmp;
	int		status;

	status = 1;
	while (cmds_amount-- > 0)
	{
		pid = waitpid(-1, &tmp, 0);
		if (pid < 0)
			handle_syserror(ECHILD);
		if (pid == last_pid && WIFEXITED(tmp))
			status = WEXITSTATUS(tmp);
		else if (pid == last_pid && WIFSIGNALED(tmp))
		{
			status = WTERMSIG(tmp);
			if (status == SIGINT)
				status = SIGERR_SIGINT;
			else if (status == SIGQUIT)
				status = SIGERR_SIGQUIT;
			if (status == SIGERR_SIGQUIT)
				ft_printff(STDERR_FILENO, "Quit: 3");
			ft_printff(STDERR_FILENO, "\n");
		}
	}
	return (status);
}

void	close_pipe(int fds[2])
{
	safe_close(&fds[READ_FD]);
	safe_close(&fds[WRITE_FD]);
}

void	redirect_fds(int read_fd, int write_fd)
{
	if (read_fd != -1 && dup2(read_fd, STDIN_FILENO) == -1)
		handle_syserror(EBUSY);
	if (write_fd != -1 && dup2(write_fd, STDOUT_FILENO) == -1)
		handle_syserror(EBUSY);
}

void	clean_exit(t_pdata *pdata)
{
	close_pdata_fds(pdata);
	exit(EXIT_FAILURE);
}
