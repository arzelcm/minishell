/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:23 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/10 00:09:20 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "environment_helper.h"
#include "utils.h"

static void	handle_chdir_err(char *value)
{
	ft_printff(STDERR_FILENO,
		"%s: cd: %s: ", PROGRAM_NAME, value);
	perror("");
}

static char	*get_dir(int argc, char **argv, t_context *context, int *pwd)
{
	char	*dir;

	dir = NULL;
	if (argc > 1)
	{
		dir = argv[1];
		if (!dir[0])
			dir = ".";
		if (ft_strcmp(dir, "-") == EQUAL_STRINGS)
		{
			dir = ft_getenv("OLDPWD", context->global_env.envp);
			if (!dir)
				handle_error("cd", "OLDPWD not set");
			*pwd = 1;
		}
		else if (access(dir, F_OK) == -1)
			return (handle_chdir_err(argv[1]), NULL);
		return (safe_ft_strdup(dir, syserr));
	}
	dir = ft_getenv("HOME", context->global_env.envp);
	if (!dir)
		ft_printff(STDERR_FILENO, "%s: cd: HOME not set\n", PROGRAM_NAME);
	return (safe_ft_strdup(dir, syserr));
}

static void	update_var(char *var, t_context *context)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putenv(var, cwd, context);
	free(cwd);
}

static void	update_var(char *var, t_context *context)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putenv(var, cwd, context);
	free(cwd);
}

int	ft_cd(int argc, char **argv, t_context *context)
{
	char	*dir;
	int		pwd;

	pwd = 0;
	dir = get_dir(argc, argv, context, &pwd);
	if (!dir)
		return (EXIT_FAILURE);
	ft_putenv("OLDPWD", "", context);
	if (ft_getenvline("PWD", context->global_env.envp))
		ft_putenv("OLDPWD", ft_getenv("PWD", context->global_env.envp), context);
	else if (ft_getenvline("PWD", context->local_env.envp))
		update_var("OLDPWD", context);
	if (chdir(dir) == -1)
		return (handle_chdir_err(dir), free(dir), EXIT_FAILURE);
	free(dir);
	if (!ft_getenvline("PWD", context->global_env.envp)
		&& !ft_getenvline("PWD", context->local_env.envp))
		return (EXIT_SUCCESS);
	update_var("PWD", context);
	if (pwd)
		ft_printf("%s\n", ft_getenv("PWD", context->global_env.envp));
	return (EXIT_SUCCESS);
}
