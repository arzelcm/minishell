/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:41 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:57:42 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_UTILS_H
# define SAFE_UTILS_H

# include <stddef.h>

void	*safe_calloc(size_t size);

void	safe_close(int *fd);

#endif