/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:23 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/03 18:35:32 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include "context.h"
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
		if (ft_strcmp(dir, "-") == EQUAL_STRINGS)
		{
			dir = ft_getenv("OLDPWD", context->global_env.envp);
			if (!dir)
				handle_error("cd", "OLDPWD not set");
			*pwd = 1;
		}
		return (safe_ft_strdup(dir, handle_syserror));
	}
	dir = ft_getenv("HOME", context->global_env.envp);
	if (!dir)
		ft_printff(STDERR_FILENO, "%s: cd: HOME not set\n", PROGRAM_NAME);
	return (safe_ft_strdup(dir, handle_syserror));
}

int	ft_cd(int argc, char **argv, t_context *context)
{
	char	*cwd;
	char	*dir;
	int		pwd;

	pwd = 0;
	dir = get_dir(argc, argv, context, &pwd);
	if (!dir)
		return (EXIT_FAILURE);
	cwd = getcwd(NULL, 0);
	ft_putenv("OLDPWD", cwd, context);
	free(cwd);
	if (chdir(dir) == -1)
	{
		handle_chdir_err(dir);
		free(dir);
		return (EXIT_FAILURE);
	}
	free(dir);
	cwd = getcwd(NULL, 0);
	ft_putenv("PWD", cwd, context);
	if (pwd)
		ft_printf("%s\n", ft_getenv("PWD", context->global_env.envp));
	free(cwd);
	return (EXIT_SUCCESS);
}
