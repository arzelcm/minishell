#include "libft.h"
#include "parser.h"
#include "utils.h"
#include "context.h"
#include <errno.h>

static int	check_cmd(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
		{
			handle_error(cmd, PERMDENIED);
			exit(PERM_ERR);
		}
		return (1);
	}
	return (0);
}

static void	check_bin(char *bin)
{
	if (access(bin, F_OK) == -1)
	{
		handle_error(bin, NOFILEDIR);
		exit(NOFDIR_ERR);
	}
	if (access(bin, X_OK) == -1)
	{
		handle_error(bin, PERMDENIED);
		exit(PERM_ERR);
	}
}

static char	*get_full_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*full_cmd_path;
	char	*tmp;

	i = 0;
	full_cmd_path = NULL;
	while (paths[i])
	{
		tmp = full_cmd_path;
		full_cmd_path = ft_strjoin(paths[i], cmd);
		if (tmp)
			free(tmp);
		if (!full_cmd_path)
			handle_syserror(ENOMEM);
		if (check_cmd(full_cmd_path))
			return (full_cmd_path);
		i++;
	}
	return (NULL);
}

void	execute_by_path(char **args, char **envp)
{
	char	*bin;
	char	*path;
	char	**paths;

	path = getenv("PATH");
	if (!path)
		path = DEF_PATH;
	paths = ft_split(path, ':');
	if (!paths)
		handle_syserror(ENOMEM);
	if (ft_strchr(args[0], '/'))
	{
		check_bin(args[0]);
		bin = args[0];
	}
	else
		bin = get_full_cmd_path(args[0], paths);
	if (!bin)
	{
		handle_error(args[0], CMDNOTFND);
		exit(NOFDIR_ERR);
	}
	execve(bin, args, envp);
	exit(EXIT_FAILURE);
}
