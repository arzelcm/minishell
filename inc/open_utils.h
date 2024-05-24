#ifndef OPEN_UTILS_H
# define OPEN_UTILS_H

# include "executor.h"
# include "token.h"

void	free_pdata(t_pdata *p_data);

void	initialize_pdata(t_pdata *p_data, t_token *token);

int		open_next_infile(t_redirection *file, int i, int *read_fd, int hdocs);

int		open_here_doc(t_redirection *here_doc);

#endif
