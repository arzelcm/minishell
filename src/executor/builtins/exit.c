#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "limits.h"
#include "environment_helper.h"
#include "builtins.h"
#include "utils.h"

// TODO: Limit to long long max and long long min n
int	ft_exit(int argc, char **argv, t_context *context)
{
	if (isatty(STDIN_FILENO))
		ft_printff(STDERR_FILENO, "exit\n");
	if (argc > 1)
	{
		if (ft_isnum(argv[1], LLONG_MAX))
			context->err_code = ft_atoi(argv[1]);
		else
		{
			ft_printff(STDERR_FILENO,
				"%s: exit: %s: numeric argument required\n",
				PROGRAM_NAME, argv[1]);
			context->err_code = ABNORMAL_EXIT_STATUS;
			custom_exit(context, 0);
		}
	}
	if (argc > 2)
	{
		handle_error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	custom_exit(context, 0);
	return (EXIT_SUCCESS);
}
