/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:49 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/09 23:26:16 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int	is_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
		return (closedir(dir), 1);
	return (0);
}

int	check_cmd(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
		{
			handle_error(cmd, NULL);
			exit(PERM_ERR);
		}
		return (1);
	}
	return (0);
}

void	check_bin(char *bin)
{
	if (access(bin, F_OK) == -1)
	{
		handle_error(bin, NULL);
		exit(NOFDIR_ERR);
	}
	if (access(bin, X_OK) == -1)
	{
		handle_error(bin, NULL);
		exit(PERM_ERR);
	}
}

char	*join_full_path(char *path, char *cmd)
{
	char	*full_cmd_path;
	char	*tmp;

	tmp = safe_ft_strjoin(path, "/", syserr);
	if (!tmp)
		syserr(ENOMEM);
	full_cmd_path = safe_ft_strjoin(tmp, cmd, syserr);
	free(tmp);
	if (!full_cmd_path)
		syserr(ENOMEM);
	return (full_cmd_path);
}
