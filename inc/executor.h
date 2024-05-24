#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "context.h"
# include "token.h"

typedef struct s_pdata
{
	pid_t	*pids;
	int		fds[2];
	int		*hd_fds;
}	t_pdata;

void	execute(t_token *token, t_context *context);

#endif
