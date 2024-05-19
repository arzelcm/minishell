#include "libft.h"
#include "environment.h"

void	free_enviroment(t_env *env)
{
	(void) env;
	ft_printf("freeing env\n");
}

void	increase_var(char *key, t_env *env)
{
	char	*value;
	char	*new_val;

	value = ft_getenv(key, env->global);
	new_val = ft_itoa(ft_atoi(value) + 1);
	ft_putenv(key, new_val, env);
	free(new_val);
}

void	print_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->global[i])
		ft_printf("%s\n", env->global[i++]);
}
