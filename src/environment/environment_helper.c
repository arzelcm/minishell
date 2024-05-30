#include "libft.h"
#include "environment.h"

void	increase_var(char *key, t_env *env)
{
	char	*value;

	value = ft_getenv(key, env->global);
	ft_putenv(key, ft_itoa(ft_atoi(value) + 1), env);
}

void	print_env(t_env *env)
{
	int	i;

	ft_printf("Enviroment %p\n", env);
	i = 0;
	while (env->global[i])
		ft_printf("%s\n", env->global[i++]);
}
