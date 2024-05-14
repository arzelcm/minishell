#include "libft.h"
#include "minishell.h"
#include "quotes_flag.h"

void	custom_exit(int exit_code)
{
	ft_printff(STDERR_FILENO, "\033[1A%sexit\n", PROMPT);
	exit(exit_code);
}

void	check_quotes(t_quotes_flag *quotes, char c)
{
	if (c == '\'' && !quotes->double_)
		quotes->simple = !quotes->simple;
	else if (c == '\"' && !quotes->simple)
		quotes->double_ = !quotes->double_;
}
