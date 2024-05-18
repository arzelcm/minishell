#include "libft.h"
#include "minishell.h"
#include "safe_utils.h"
#include "quotes_flag.h"
#include <errno.h>

void	custom_exit(int exit_code)
{
	ft_printff(STDERR_FILENO, "\033[1A%sexit\n", PROMPT);
	exit(exit_code);
}

void	push_char(char	**str, char c)
{
	char	*new_word;
	int		len;

	len = ft_strlen(*str);
	new_word = safe_calloc(sizeof(char) * (len + 2));
	ft_strlcpy(new_word, *str, -1);
	new_word[len] = c;
	new_word[len + 1] = '\0';
	free(*str);
	*str = new_word;
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
