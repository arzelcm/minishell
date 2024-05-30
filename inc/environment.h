#ifndef environment_H
# define environment_H

typedef struct s_env
{
	char	**envp;
	int		size;
}	t_env;

void	init_env(t_env *global, t_env *local, char **envp);

char	*ft_getenv(char *key, char **envp);

void	ft_putenv(char *key, char *value, t_env *env);

#endif