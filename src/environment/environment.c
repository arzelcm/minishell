/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:18 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/04 21:36:40 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "safe_utils.h"
#include "environment.h"
#include "environment_helper.h"
#include "limits.h"
#include "context.h"
#include "utils.h"

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
	return (1);
}

static char	*set_vars(char *value, char *key, t_env **env, t_context *context)
{
	char	*complete_val;

	if (!value)
	{
		if (ft_getenvline(key, context->global_env.envp))
			return (NULL);
		*env = &context->local_env;
		complete_val = safe_ft_strdup("", handle_syserror);
	}
	else
	{
		ft_deleteenv(key, &context->local_env);
		*env = &context->global_env;
		complete_val = safe_strjoin("=", value, handle_syserror);
	}
	return (complete_val);
}

void	ft_putenv(char *key, char *value, t_context *context)
{
	char	*complete_val;
	char	**curr_envp;
	char	**line;
	t_env	*env;

	complete_val = set_vars(value, key, &env, context);
	if (!complete_val)
		return ;
	line = ft_getenvline(key, env->envp);
	if (line)
	{
		free(*line);
		*line = safe_strjoin(key, complete_val, handle_syserror);
	}
	else
	{
		curr_envp = safe_calloc(sizeof(char *) * ((env->size) + 2));
		copy_envp(curr_envp, env->envp, 0);
		curr_envp[env->size] = safe_strjoin(key, complete_val, handle_syserror);
		curr_envp[env->size + 1] = NULL;
		env->size++;
		free(env->envp);
		env->envp = curr_envp;
	}
	free(complete_val);
}

void	init_env(t_context *context, char **envp)
{
	char	*cwd;

	ft_bzero(&context->global_env, sizeof(t_env));
	ft_bzero(&context->local_env, sizeof(t_env));
	context->global_env.size = 0;
	while (envp[context->global_env.size])
		context->global_env.size++;
	context->global_env.envp = safe_calloc(sizeof(char *)
			* (context->global_env.size + 2));
	copy_envp(context->global_env.envp, envp, 1);
	increase_shlevel("SHLVL", context);
	cwd = getcwd(NULL, 0);
	ft_putenv("PWD", cwd, context);
	free(cwd);
	context->local_env.size = 0;
	context->local_env.envp = safe_calloc(sizeof(char *) * 2);
	ft_deleteenv("OLDPWD", &context->global_env);
	ft_putenv("OLDPWD", NULL, context);
}
