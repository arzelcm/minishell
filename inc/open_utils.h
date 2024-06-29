/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:29 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:57:29 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_UTILS_H
# define OPEN_UTILS_H

# include "token.h"

int	fork_here_doc(t_redirection *here_doc);

int	open_infile(char *path);

int	open_outfile(char *path, int mode);

#endif
