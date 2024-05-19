#include "libft.h"
#include "safe_utils.h"
#include "environment.h"

// TODO: INCREASE $SHLVL & SET \?\ ENV VARIABLE TO CONTROL ERR_CODE
// TODO: FREE environment
// REVIEW!!!
char	*ft_getenv(char *key, char **envp)
{
	char	*val;
	int		i;
	int		key_len;
	int		found;

	if (!*key)
		return (NULL);
	found = 0;
	val = NULL;
	i = 0;
	key_len = ft_strlen(key);
	while (envp[i] && !found)
	{
		found = ft_strncmp(key, envp[i++], key_len) == EQUAL_STRINGS;
	}
	if (found)
	{
		val = ft_strchr(envp[i], '=');
		if (val && *val == '=')
			val++;
		else
			val = NULL;
	}
	ft_printf("got env_var\nkey -> %s\nval-> %s\nenv[i]: -> %s\ni -> %i\n", key, val, envp[i], i);
	return (val);
}

void	copy_envp(char **dst, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
}

void	print_env(t_env *env)
{
	int	i;

	ft_printf("Enviroment %p\n", env);
	i = 0;
	while (env->global[i])
		ft_printf("%s\n", env->global[i++]);
}

void	ft_putenv(char *key, char *value, t_env *env)
{
	char *complete_key;
	char	**envp;

	// TODO: Check duplicates
	ft_getenv(key, env->global);
	complete_key = ft_strjoin(key, "=");
	envp = safe_calloc(sizeof(char *) * (env->global_size + 2));
	copy_envp(envp, env->global);
	free(env->global);
	env->global = envp;
	env->global[env->global_size] = ft_strjoin(complete_key, value);
	env->global[env->global_size + 1] = NULL;
	ft_printf("env_var: %s\n", env->global[env->global_size]);
	env->global_size++;
	print_env(env);
}

void	init_env(t_env *env, char **envp)
{
	int	i;

	ft_bzero(env, sizeof(t_env));
	i = 0;
	
	while (envp[i])
		i++;
	env->global_size = i;
	env->global = safe_calloc(sizeof(char *) * (env->global_size + 2));
	copy_envp(env->global, envp);
	print_env(env);
}