#ifndef OPEN_UTILS_H
# define OPEN_UTILS_H

# include "token.h"

int		open_next_infile(t_redirection *file, int i, int *read_fd, int hdocs);

int		open_here_doc(int fds[2], t_redirection *here_doc);

#endif
