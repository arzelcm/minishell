#include "libft.h"
#include "execute_command.h"
#include "execute_command_utils.h"
#include "executor_utils.h"
#include "open.h"
#include "signals.h"
#include "builtins.h"
#include "utils.h"
#include <errno.h>

static char	*get_full_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*full_cmd_path;
	char	*tmp;

	i = 0;
	full_cmd_path = NULL;
	if (!cmd[0] || ft_strcmp(cmd, ".") == EQUAL_STRINGS
		|| ft_strcmp(cmd, "..") == EQUAL_STRINGS)
		return (NULL);
	while (paths[i])
	{
		tmp = full_cmd_path;
		full_cmd_path = join_full_path(paths[i], cmd);
		if (tmp)
			free(tmp);
		if (!full_cmd_path)
			handle_syserror(ENOMEM);
		if (check_cmd(full_cmd_path))
			return (full_cmd_path);
		i++;
	}
	free(full_cmd_path);
	return (NULL);
}

static void	execute_by_path(char **args, char **envp)
{
	char	*bin;
	char	*path;
	char	**paths;

	path = ft_getenv("PATH", envp);
	if (!path)
		path = DEF_PATH;
	paths = ft_split(path, ':');
	if (!paths)
		handle_syserror(ENOMEM);
	bin = args[0];
	if (ft_strchr(bin, '/'))
		check_bin(bin);
	else
		bin = get_full_cmd_path(bin, paths);
	if (!bin)
	{
		handle_error(args[0], CMDNOTFND);
		exit(NOFDIR_ERR);
	}
	execve(bin, args, envp);
	exit(EXIT_FAILURE);
}

void	execute_command(t_pdata *pdata, t_token *token, t_context *context)
{
	listen_signals(SUBPROCESS, SUBPROCESS);
	if (!open_files(pdata, token->redirections, token->here_docs, context))
		clean_exit(pdata);
	redirect_fds(pdata->fds[READ_FD], pdata->fds[WRITE_FD]);
	close_pdata_fds(pdata);
	expand_args(token, context);
	if (!token->argc)
		exit(EXIT_SUCCESS);
	if (is_builtin(token->args[0]))
		exit(execute_builtin(token->args[0], token, context));
	if (!ft_strchr(token->args[0], '/') || !is_directory(token->args[0]))
		execute_by_path(token->args, context->global_env.envp);
	handle_error(token->args[0], ISDIRECTORY);
	exit(PERM_ERR);
}
