/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:57:31 by arcanava          #+#    #+#             */
/*   Updated: 2024/06/29 21:57:31 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_H
# define OPEN_H

# define HERE_DOC_PREFIX "> "
# include "token.h"
# include "pdata_helpers.h"

enum e_fd_indexes
{
	READ_FD,
	WRITE_FD
};

int	open_here_doc(int fds[2], t_redirection *here_doc);

int	open_here_docs(t_redirection *infiles, int here_docs_amount);

int	open_files(t_pdata *pdata, t_redirection *redirs,
		int hds_amnt, t_context *context);

#endif
