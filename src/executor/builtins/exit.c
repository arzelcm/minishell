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
			c_exit(context);
		}
	}
	if (argc > 2)
	{
		ft_printff(STDERR_FILENO, "%s: exit: too many arguments\n",
			PROGRAM_NAME);
		return (EXIT_FAILURE);
	}
	c_exit(context);
	return (EXIT_SUCCESS);
}