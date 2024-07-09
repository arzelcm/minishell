/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:58:04 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/09 23:26:16 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "context.h"

void	custom_exit(t_context *context, int print);

void	push_char(char	**str, char c);

void	syserr(int errnum);

void	handle_error(char *file, char *message);

char	*quote_str(char *str);

void	push_str(char **s1, char *s2);

#endif