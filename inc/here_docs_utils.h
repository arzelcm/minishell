/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:31:55 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/07/14 20:14:22 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOCS_UTILS_H
# define HERE_DOCS_UTILS_H

# include "token.h"

void	initialize_heredocs(t_token *token);

void	close_here_docs(t_token *token);

#endif
