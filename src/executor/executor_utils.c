#include "libft.h"
#include "context.h"
#include "safe_utils.h"
#include "utils.h"
#include "open.h"
#include <fcntl.h>
#include <errno.h>

int	wait_child_processes(pid_t last_pid, int cmds_amount)
{
	pid_t	pid;
	int		tmp;
	int		status;

	status = 1;
	while (cmds_amount > 0)
	{
		pid = waitpid(-1, &tmp, 0);
		if (pid < 0)
			handle_syserror(ECHILD);
		if (pid == last_pid && WIFEXITED(tmp))
			status = WEXITSTATUS(tmp);
		cmds_amount--;
	}
	return (status);
}

int	is_a_builtin(char *command)
{
	if (ft_strchr(command, '/'))
		return (0);
	return (0);
}

void	close_pipe(int fds[2])
{
	safe_close(&fds[READ_FD]);
	safe_close(&fds[WRITE_FD]);
}

int	open_infile(char *path)
{
	int		fd;
	char	*quoted_file;

	if (access(path, F_OK) == -1)
		return (handle_error(path, NOFILEDIR), -1);
	if (access(path, R_OK) == -1)
		return (handle_error(path, PERMDENIED), -1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		quoted_file = quote_str(path);
		handle_error("open: Error trying open file", quoted_file);
		free(quoted_file);
		return (-1);
	}
	return (fd);
}

int	open_outfile(char *path, int mode)
{
	int		fd;
	int		flags;
	char	*quoted_file;

	if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
		return (handle_error(path, PERMDENIED), -1);
	flags = O_CREAT | O_WRONLY;
	if (mode == APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(path, flags, PERMBITS);
	if (fd < 0)
	{
		quoted_file = quote_str(path);
		handle_error("open: Error trying open file", quoted_file);
		free(quoted_file);
		return (-1);
	}
	return (fd);
}
