#ifndef environment_H
# define environment_H

typedef struct s_env
{
	char	**global;
	int		global_size;
	char	**local;
	int		local_size;
}	t_env;


void	init_env(t_env *env, char **envp);

char	*ft_getenv(char *key, char **envp);

void	ft_putenv(char *key, char *value, t_env *env);


#endif