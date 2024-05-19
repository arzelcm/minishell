#ifndef CONTEXT_H
# define CONTEXT_H
# define PERM_ERR 126
# define NOFDIR_ERR 127
# define SYNTAX_ERROR 258

# define CMDNOTFND "command not found"
# define NOFILEDIR "No such file or directory"
# define PERMDENIED "Permission denied"
# define ISDIRECTORY "is a directory"
# define PERMBITS 0644

#include "environment.h"

typedef struct s_context
{
	int		err_code;
	t_env	env;
}	t_context;

#endif
