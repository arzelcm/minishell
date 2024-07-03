/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:14 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/03 18:31:00 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "context.h"
#include "safe_libft.h"
#include "utils.h"

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
		new_val = safe_ft_strdup("", handle_syserror);
	else
		new_val = safe_itoa(num + 1);
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
			dst[i] = safe_ft_strdup(src[i], handle_syserror);
		else
			dst[i] = src[i];
		i++;
	}
}

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
