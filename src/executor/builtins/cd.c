#include "minishell.h"
#include "libft.h"
#include "context.h"
#include <unistd.h>

static void	handle_chdir_err(char *value, t_context *context)
{
	ft_printff(STDERR_FILENO,
		"%s: cd: %s: ", PROGRAM_NAME, value);
	perror("");
	context->err_code = 1;
}

int	ft_cd(int argc, char **argv, t_context *context)
{
	char	*cwd;
	char	*dir;

	if (argc > 1)
		dir = argv[1];
	else
	{
		dir = ft_getenv("HOME", context->global_env.envp);
		if (!dir)
		{
			ft_printff(STDERR_FILENO, "%s: cd: HOME not set\n", PROGRAM_NAME);
			context->err_code = 1;
			return (EXIT_FAILURE);
		}
	}
	cwd = getcwd(NULL, 0);
	ft_putenv("OLDPWD", cwd, context);
	free(cwd);
	if (chdir(dir) == -1)
		handle_chdir_err(argv[1], context);
	cwd = getcwd(NULL, 0);
	ft_putenv("PWD", cwd, context);
	free(cwd);
	return (EXIT_SUCCESS);
}
