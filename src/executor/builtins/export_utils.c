/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:31:56 by chris             #+#    #+#             */
/*   Updated: 2024/07/05 13:07:32 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "environment.h"
#include "utils.h"

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
	key = safe_ft_substr(str, 0,
			ft_strchr(str, delimiter) - str, handle_syserror);
	return (key);
}

void	update_env(char *key, char *value, int export_mode, t_context *context)
{
	char	*new_value;
	char	*curr_value;

	curr_value = ft_getenv(key, context->global_env.envp);
	if (export_mode == EXPMODE_TRUNC || !curr_value || !curr_value[0])
		return (ft_putenv(key, value, context));
	new_value = safe_ft_strjoin(curr_value, value, handle_syserror);
	ft_putenv(key, new_value, context);
	free(new_value);
}
