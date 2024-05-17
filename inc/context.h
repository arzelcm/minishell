#ifndef CONTEXT_H
# define CONTEXT_H
# define PERM_ERR 126
# define NOFDIR_ERR 127
# define SYNTAX_ERROR 258

# define CMDNOTFND "command not found"
# define NOFILEDIR "No such file or directory"
# define PERMDENIED "Permission denied"
# define PERMBITS 0666
typedef struct s_context
{
	int		err_code;
	char	**envp;
}	t_context;

#endif
