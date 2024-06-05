#include "libft.h"
#include "environment.h"
#include "context.h"

void	free_environment(t_env *env)
{
	free_matrix(env->envp);
}

void	increase_var(char *key, t_context *context)
{
	char	*value;
	char	*new_val;
	int		num;

	value = ft_getenv(key, context->global_env.envp);
	num = ft_atoi(value);
	if (num == 999)
		new_val = ft_strdup("");
	else
		new_val = ft_itoa(num + 1);
	ft_putenv(key, new_val, context);
	free(new_val);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		ft_printf("%s\n", env[i++]);
}

void	copy_envp(char **dst, char **src, int duplicate)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		if (duplicate)
			dst[i] = ft_strdup(src[i]);
		else
			dst[i] = src[i];
		i++;
	}
}
