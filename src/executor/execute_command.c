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
	if (!cmd[0])
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
	pdata->fds[READ_FD] = \
		open_infiles(pdata->fds[READ_FD], token->infiles, token->here_docs);
	if (token->infiles && pdata->fds[READ_FD] == -1)
		clean_exit(pdata);
	pdata->fds[WRITE_FD] = open_outfiles(pdata->fds[WRITE_FD], token->outfiles);
	if (token->outfiles && pdata->fds[WRITE_FD] == -1)
		clean_exit(pdata);
	redirect_fds(pdata->fds[READ_FD], pdata->fds[WRITE_FD]);
	close_pdata_fds(pdata);
	if (!token->argc)
		exit(EXIT_SUCCESS);
	if (is_builtin(token->args[0]))
		exit(execute_builtin(token->args[0], token, context));
	if (!is_directory(token->args[0]))
		execute_by_path(token->args, context->global_env.envp);
	handle_error(token->args[0], ISDIRECTORY);
	exit(PERM_ERR);
}
