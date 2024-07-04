/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helper.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:56:51 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/04 21:40:26 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_HELPER_H
# define ENVIRONMENT_HELPER_H

# ifndef SHLVL_MAX_LEN
#  define SHLVL_MAX_LEN 3
# endif

# include "environment.h"

void	increase_shlevel(char *key, t_context *context);

void	print_env(char **env);

void	free_environment(t_env *env);

void	copy_envp(char **dst, char **src, int duplicate);

char	**ft_getenvline(char *key, char **envp);

#endif