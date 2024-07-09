/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:37 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/09 23:26:16 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include <errno.h>

void	*safe_calloc(size_t size)
{
	void	*allocation;

	allocation = ft_calloc(1, size);
	if (!allocation)
		syserr(ENOMEM);
	return (allocation);
}

void	safe_close(int *fd)
{
	if (*fd == -1)
		return ;
	if (close(*fd) == -1)
		exit(EBADF);
	*fd = -1;
}
