/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:15 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/06 21:07:04 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSOR_H
# define EXPANSOR_H

# include "context.h"
# include "quotes_flag.h"

typedef struct s_expansion
{
	int	expanded;
	int	quoted;
}	t_expansion;

int		expand(char **line, t_context *context, t_expansion *expansion);

int		variable_finished(char c, int not_first, char *var);

void	init_vars(t_quotes_flag *quotes, int *i, int *j);

#endif