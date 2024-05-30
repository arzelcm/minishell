#include "libft.h"
#include "safe_utils.h"
#include "environment.h"
#include "environment_helper.h"
#include "limits.h"

// TODO: FREE environment
// REVIEW!!!
// TODO: Implement local vars

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
	while (envp && envp[i] && !found)
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
	// ft_printf("got env_var\nkey -> %s\nval-> %s\n", key, val);
	return (val);
}

void	copy_envp(char **dst, char **src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
}

void	ft_putenv(char *key, char *value, t_env *env)
{
	char	*complete_val;
	char	**curr_envp;
	char	**line;

	if (!value)
		complete_val = ft_strdup("");
	else
		complete_val = ft_strjoin("=", value);
	line = ft_getenvline(key, env->envp);
	if (line)
	{
		free(*line);
		*line = ft_strjoin(key, complete_val);
	}
	else
	{
		curr_envp = safe_calloc(sizeof(char *) * ((env->size) + 2));
		copy_envp(curr_envp, env->envp);
		curr_envp[env->size] = ft_strjoin(key, complete_val);
		curr_envp[env->size + 1] = NULL;
		(env->size)++;
		free(env->envp);
		env->envp = curr_envp;
	}
	free(complete_val);
}

void	init_env(t_env *global, t_env *local,  char **envp)
{
	int	i;

	ft_bzero(global, sizeof(t_env));
	ft_bzero(local, sizeof(t_env));
	i = 0;
	while (envp[i])
		i++;
	global->size = i;
	global->envp = safe_calloc(sizeof(char *) * (global->size + 2));
	copy_envp(global->envp, envp);
	local->size = 0;
	local->envp = safe_calloc(sizeof(char *) * 2);
	increase_var("SHLVL", global);
}
