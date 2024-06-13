#ifndef EXECUTE_COMMAND_H
# define EXECUTE_COMMAND_H

# include "pdata_helpers.h"
# include "context.h"

# define DEF_PATH "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"

void	execute_command(t_pdata *pdata, t_token *token, t_context *context);

#endif
