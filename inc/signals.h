#ifndef SIGNALS_H
# define SIGNALS_H

typedef enum e_echoctl_mode
{	
	OFF,
	ON
}	t_echoctl_mode;

typedef enum e_signals_mode
{	
	MAIN,
	SUBPROCESS,
	EXECUTOR,
	HEREDOC
}	t_signals_mode;

void	listen_signals(int sigquit_mode, int sigint_mode);

void	config_echoctl_terminal(int mode);

#endif
