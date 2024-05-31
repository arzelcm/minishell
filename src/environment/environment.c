#include "libft.h"
#include "safe_utils.h"
#include "environment.h"
#include "environment_helper.h"
#include "limits.h"
#include "context.h"

char	**ft_getenvline(char *key, char **envp)
{
	int		i;
	int		found;
	int		key_len;

	key_len = ft_strlen(key);
	found = 0;
	i = 0;
	while (envp && envp[i] && !found)
	{
		found = ft_strncmp(key, envp[i], key_len) == EQUAL_STRINGS
			&& (envp[i][key_len] == '=' || envp[i][key_len] == '\0');
		if (!found)
			i++;
	}
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
	return (val);
}

int	ft_deleteenv(char *key, t_env *env)
{
	char	**line;
	char	**new_env;
	int		i;
	int		j;

	line = ft_getenvline(key, env->envp);
	if (!line)
		return (0);
	new_env = safe_calloc(sizeof(char *) * (env->size));
	i = 0;
	j = 0;
	while (env->envp[i])
	{
		if (ft_strcmp(env->envp[i], *line) == EQUAL_STRINGS)
			free(*line);
		else
			new_env[j++] = env->envp[i];
		i++;
	}
	new_env[j] = NULL;
	free(env->envp);
	env->envp = new_env;
	env->size--;
	print_env(env->envp);
	return (1);
}

// TODO: REFACTOR!
void	ft_putenv(char *key, char *value, t_context *context)
{
	char	*complete_val;
	char	**curr_envp;
	char	**line;
	t_env	*env;

	if (!value)
	{
		if (ft_getenvline(key, context->global_env.envp))
			return ;
		env = &context->local_env;
		complete_val = ft_strdup("");
	}
	else
	{
		ft_deleteenv(key, &context->local_env);
		env = &context->global_env;
		complete_val = ft_strjoin("=", value);
	}
	line = ft_getenvline(key, env->envp);
	if (line)
	{
		free(*line);
		*line = ft_strjoin(key, complete_val);
	}
	else
	{
		curr_envp = safe_calloc(sizeof(char *) * ((env->size) + 2));
		copy_envp(curr_envp, env->envp, 0);
		curr_envp[env->size] = ft_strjoin(key, complete_val);
		curr_envp[env->size + 1] = NULL;
		env->size++;
		free(env->envp);
		env->envp = curr_envp;
	}
	free(complete_val);
}

void	init_env(t_context *context, char **envp)
{
	int	i;

	ft_bzero(&context->global_env, sizeof(t_env));
	ft_bzero(&context->local_env, sizeof(t_env));
	i = 0;
	while (envp[i])
		i++;
	context->global_env.size = i;
	context->global_env.envp = safe_calloc(sizeof(char *)
			* (context->global_env.size + 2));
	copy_envp(context->global_env.envp, envp, 1);
	context->local_env.size = 0;
	context->local_env.envp = safe_calloc(sizeof(char *) * 2);
	increase_var("SHLVL", context);
}
