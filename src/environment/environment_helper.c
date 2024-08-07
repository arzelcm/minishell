/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:14 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/15 21:07:10 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "environment.h"
#include "context.h"
#include "safe_libft.h"
#include "utils.h"
#include "environment_helper.h"
#include <limits.h>

void	free_environment(t_env *env)
{
	free_matrix(env->envp);
}

// TODO: free new_val
void	increase_shlevel(char *key, t_context *context)
{
	char			*value;
	char			*new_val;
	int				num;
	int				is_num;

	value = ft_getenv(key, context->global_env.envp);
	num = ((int) ft_atol(value)) + 1;
	new_val = safe_itoa(num);
	is_num = ft_isnum(value);
	if (value && ft_strcmp(SHLVL_MAX, new_val) == EQUAL_STRINGS)
		new_val = ft_override_val(new_val, safe_ft_strdup("", syserr));
	else if (*new_val == '-')
		new_val = ft_override_val(new_val, safe_ft_strdup("0", syserr));
	else if (!value || !is_num || ft_strlen(new_val) > SHLVL_MAX_LEN)
	{
		if (value && is_num && num > 0)
			ft_printff(STDERR_FILENO,
				"%s: warning: shell level (%s) too high, resetting to 1\n",
				PROGRAM_NAME, new_val);
		new_val = ft_override_val(new_val, safe_ft_strdup("1", syserr));
	}
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
			dst[i] = safe_ft_strdup(src[i], syserr);
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
