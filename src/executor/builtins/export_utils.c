/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:31:56 by chris             #+#    #+#             */
/*   Updated: 2024/07/04 16:01:13 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "environment.h"

char	*get_key(char *str, int *export_mode)
{
	char	*key;
	char	delimiter;
	
	if (ft_strnstr(str, "+=", ft_strchr(str, '=') - str + 1))
	{
		delimiter = '+';
		*export_mode = EXPMODE_APPEND;
	}
	else
	{
		delimiter = '=';
		*export_mode = EXPMODE_TRUNC;
	}
	key = ft_substr(str, 0, ft_strchr(str, delimiter) - str);
	return (key);
}

void	update_env(char *key, char *value, int export_mode, t_context *context)
{
	char	*new_value;
	char	*curr_value;

	curr_value = ft_getenv(key, context->global_env.envp);
	if (export_mode == EXPMODE_TRUNC || !curr_value || !curr_value[0])
		return (ft_putenv(key, value, context));
	new_value = ft_strjoin(curr_value, value);
	ft_putenv(key, new_value, context);
	free(new_value);
}
