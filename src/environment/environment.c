#include "libft.h"
#include "safe_utils.h"
#include "environment.h"
#include "environment_helper.h"

// TODO: INCREASE $SHLVL & SET \?\ ENV VARIABLE TO CONTROL ERR_CODE
// TODO: FREE environment
// REVIEW!!!
char	**ft_getenvline(char *key, char **envp)
{
	int		i;
	int		found;
	int		key_len;
	char	*complete_key;

	complete_key = ft_strjoin(key, "=");
	key_len = ft_strlen(complete_key);
	found = 0;
	i = 0;
	while (envp[i] && !found)
	{
		found = ft_strncmp(complete_key, envp[i], key_len) == EQUAL_STRINGS;
		if (!found)
			i++;
	}
	free(complete_key);
	if (found)
		return (envp + i);
	else
		return (NULL);
}

char	*ft_getenv(char *key, char **envp)
{
	char	*val;
	char	**line;

	if (!*key)
		return (NULL);
	val = NULL;
	line = ft_getenvline(key, envp);
	if (line && *line)
	{
		val = ft_strchr(*line, '=');
		if (val)
			val++;
		else
			val = NULL;
	}
	// ft_printf("got env_var\nkey -> %s\nval-> %s\nenv[i]: -> %s\ni -> %i\n", key, val, envp[i], i);
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

void	ft_putenv(char *key, char *value, t_env *env)
{
	char	*complete_key;
	char	**envp;
	char	**line;

	key = ft_strtrim(key, " ");
	complete_key = ft_strjoin(key, "=");
	line = ft_getenvline(key, env->global);
	free(key);
	if (line)
	{
		*line = ft_strjoin(complete_key, value);
		return ;
	}
	envp = safe_calloc(sizeof(char *) * (env->global_size + 2));
	copy_envp(envp, env->global);
	free(env->global);
	env->global = envp;
	env->global[env->global_size] = ft_strjoin(complete_key, value);
	env->global[env->global_size + 1] = NULL;
	env->global_size++;
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
	increase_var("SHLVL", env);
}
