#ifndef PDATA_HELPERS_H
# define PDATA_HELPERS_H

# include "token.h"
# include <stdlib.h>

typedef struct s_pdata
{
	pid_t	*pids;
	int		std_fds[2];
	int		fds[2];
	int		pipe_fds[2];
	int		last_pipe;
	int		*heredocs_fds;
}	t_pdata;

void	free_pdata(t_pdata *p_data);

void	close_pdata_fds(t_pdata *pdata);

void	save_backup_stdfds(t_pdata *p_data);

void	initialize_pdata(t_pdata *p_data, t_token *token);

#endif
