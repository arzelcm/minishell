#ifndef OPEN_UTILS_H
# define OPEN_UTILS_H

# include "token.h"

int	fork_here_doc(t_redirection *here_doc);

int	open_infile(char *path);

int	open_outfile(char *path, int mode);

#endif
