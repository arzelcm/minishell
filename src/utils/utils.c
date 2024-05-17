#include "libft.h"
#include "minishell.h"
#include "quotes_flag.h"
#include <errno.h>

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

void	handle_syserror(int errnum)
{
	perror(PROGRAM_NAME);
	exit(errnum);
}

void	handle_error(char *file, char *message)
{
	ft_printff(STDERR_FILENO, "%s: %s: %s\n", PROGRAM_NAME, file, message);
}

char	*quote_str(char *str)
{
	char	*tmp;
	char	*quoted_str;

	tmp = ft_strjoin("`", str);
	if (!tmp)
		handle_syserror(ENOMEM);
	quoted_str = ft_strjoin(tmp, "'");
	if (!quoted_str)
		handle_syserror(ENOMEM);
	free(tmp);
	return (quoted_str);	
}
