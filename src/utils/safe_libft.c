/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:06:43 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/09 23:26:16 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "utils.h"
#include <errno.h>

char	*safe_itoa(int n)
{
	char	*result;

	result = ft_itoa(n);
	if (!result)
		syserr(ENOMEM);
	return (result);
}

char	*safe_ltoa(long n)
{
	char	*result;

	result = ft_ltoa(n);
	if (!result)
		syserr(ENOMEM);
	return (result);
}
