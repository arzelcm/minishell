#include "signals.h"
#include "libft.h"
#include "context.h"
#include "readline.h"
#include <unistd.h>
#include <termios.h>
#include <signal.h>

static void	catch_sigint_heredoc(int signal)
{
	g_sigval = signal;
	if (signal != SIGINT)
		return ;
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	ft_printf("\n");
	exit(EXIT_FAILURE);
}

static void	catch_sigint_prompt(int signal)
{
	g_sigval = signal;
	if (signal != SIGINT)
		return ;
	ft_printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	listen_signals(int sigquit_mode, int sigint_mode)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigquit_mode == MAIN || sigquit_mode == HEREDOC)
		sa.__sigaction_u.__sa_handler = SIG_IGN;
	else if (sigquit_mode == SUBPROCESS)
		sa.__sigaction_u.__sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
	if (sigint_mode == MAIN)
		sa.__sigaction_u.__sa_handler = catch_sigint_prompt;
	else if (sigint_mode == SUBPROCESS)
		sa.__sigaction_u.__sa_handler = SIG_DFL;
	else if (sigint_mode == EXECUTOR)
		sa.__sigaction_u.__sa_handler = SIG_IGN;
	else if (sigint_mode == HEREDOC)
		sa.__sigaction_u.__sa_handler = catch_sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

void	config_echoctl_terminal(int mode)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	if (mode == OFF && (termios.c_lflag & ECHOCTL))
		termios.c_lflag &= ~ECHOCTL;
	if (mode == ON && !(termios.c_lflag & ECHOCTL))
		termios.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}
