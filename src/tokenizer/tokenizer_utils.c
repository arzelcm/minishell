#include "safe_utils.h"
#include "libft.h"
#include "utils.h"

void	avoid_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

char	*get_word(char	*str, int *i)
{
	char	*word;
	char	quote;

	word = safe_calloc(sizeof(char));
	avoid_spaces(str, i);
	while (str[*i] != '\0' && !ft_stroccurrences("| <>&", str[*i]))
	{
		quote = '\0';
		if (str[*i] == '\'')
			quote = '\'';
		else if (str[*i] == '\"')
			quote = '\"';
		if (quote)
		{
			(*i)++;
			while (quote && str[*i] != quote)
				push_char(&word, str[(*i)++]);
			(*i)++;
		}
		else
			push_char(&word, str[(*i)++]);
	}
	return (word);
}
