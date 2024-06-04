#include "minishell.h"
#include "libft.h"
#include "context.h"
#include "limits.h"
#include "environment_helper.h"
#include "builtins.h"
#include "utils.h"

int	ft_exit(int argc, char **argv, t_context *context)
{
	ft_printff(STDERR_FILENO, "exit\n");
	if (argc > 1)
	{
		ft_printf("is_num?: %i\n", ft_isnum(argv[1], LLONG_MAX));
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
		context->err_code = EXIT_FAILURE;
		return (1);
	}
	c_exit(context);
	return (1);
}
