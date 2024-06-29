/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:56:54 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:56:55 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_env
{
	char	**envp;
	int		size;
}	t_env;

typedef struct s_context	t_context;

void	init_env(t_context *context, char **envp);

char	*ft_getenv(char *key, char **envp);

void	ft_putenv(char *key, char *value, t_context *context);

int		ft_deleteenv(char *key, t_env *env);

#endif