/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_vars.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:12 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/06 21:18:15 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSOR_VARS_H
# define EXPANSOR_VARS_H

# include "context.h" 

typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_vars
{
	int		size;
	int		keys_length;
	int		values_length;
	t_var	*list;
}	t_vars;

void	fill_needed_vars(t_vars *vars, char *line, t_context *context);

void	free_expansor_vars(t_var *var);

t_var	*get_var(char *key, t_vars *vars, t_context *context);

#endif