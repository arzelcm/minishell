#include "libft.h"
#include "minishell.h"
#include "safe_utils.h"

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