/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:56:56 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:56:57 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_COMMAND_UTILS_H
# define EXECUTE_COMMAND_UTILS_H

int		is_directory(char *path);

int		check_cmd(char *cmd);

void	check_bin(char *bin);

char	*join_full_path(char *path, char *cmd);

#endif
