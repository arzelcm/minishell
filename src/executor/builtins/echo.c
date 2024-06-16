#include "libft.h"
#include "context.h"

int	ft_echo(int argc, char **argv, t_context *context)
{
	int	i;
	int	new_line;

	(void) context;
	new_line = 1;
	i = 1;
	while (argc > 1 && i < argc && *argv[i] == '-' && ft_strlen(argv[i]) > 1
		&& ft_stroccurrences(argv[i], 'n') == (int) ft_strlen(argv[i]) - 1)
	{
		new_line = 0;
		i++;
	}
	while (i < argc)
	{
		ft_printf("%s", argv[i++]);
		if (i < argc)
			ft_printf(" ");
	}
	if (new_line)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
