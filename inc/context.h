#ifndef CONTEXT_H
# define CONTEXT_H
# define PERM_ERR 126
# define NOFDIR_ERR 127
# define SYNTAX_ERROR 258

# define CMDNOTFND "command not found"
# define NOFILEDIR "No such file or directory"
# define PERMDENIED "Permission denied"
# define ISDIRECTORY "is a directory"
# define ISDIRECTORY_U "Is a directory"
# define PERMBITS 0644
# define SIGERR_SIGINT 130
# define SIGERR_SIGQUIT 131

# include "environment.h"

extern int	g_sigval;

typedef struct s_context
{
	int		err_code;
	t_env	local_env;
	t_env	global_env;
}	t_context;

#endif
