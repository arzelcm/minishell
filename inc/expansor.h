/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:15 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:57:16 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSOR_H
# define EXPANSOR_H
# include "context.h"

typedef struct s_expansion
{
	int	expanded;
	int	quoted;
}	t_expansion;

int	expand(char **line, t_context *context, t_expansion *expansion);

int	variable_finished(char c, int not_first);

#endif