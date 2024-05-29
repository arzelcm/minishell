#include "libft.h"
#include "context.h"

int	ft_echo(int argc, char **argv, t_context *context)
{
	int	i;

	(void) context;
	i = 1;
	if (argc == 1)
	{
		ft_printf("\n");
		return (1);
	}
	if (ft_strcmp(argv[1], "-n") == EQUAL_STRINGS)
		i = 2;
	while (i < argc)
	{
		ft_printf("%s", argv[i++]);
		if (i == argc - 1)
			ft_printf(" ");
	}
	if (ft_strcmp(argv[1], "-n") != EQUAL_STRINGS)
		ft_printf("\n");
	return (1);
}
