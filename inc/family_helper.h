/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_helper.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:09:15 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/12 10:30:06 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAMILY_HELPER_H
# define FAMILY_HELPER_H

# include "token.h"

int		set_parent(char *line, int *i, t_token **parent, t_token **current);

void	create_parent(t_token **current, t_token *new_parent,
			t_token **parent, int new_cmd);

#endif