#ifndef REDIRECTION_H
# define REDIRECTION_H

# define HERE_DOC_PREFIX "> "
# include "token.h"

enum fd_indexes
{
	READ_FD,
	WRITE_FD
};

int	open_here_docs(t_redirection *infiles, int here_docs_amount);

int	open_infiles(int read_fd, t_redirection *infiles, int here_docs_amount);

int	open_outfiles(int write_fd, t_redirection *outfiles);

#endif
