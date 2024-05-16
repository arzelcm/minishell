#include "safe_utils.h"
#include "libft.h"
#include "utils.h"
#include "expansor.h"
#include "quotes_utils.h"

void	avoid_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

int	get_word_len(char *str, int i)
{
	int	start_i;

	start_i = i;
	while (str[i] != '\0' && !ft_stroccurrences("| <>&", str[i]))
	{
		if (!avoid_quotes(str, &i))
			i++;
	}
	return (i - start_i);
}

void	fill_word(int len, char *str, char **word)
{
	char	quote;
	int		j;

	j = 0;
	while (j < len)
	{
		quote = '\0';
		if (str[j] == '\'')
			quote = '\'';
		else if (str[j] == '\"')
			quote = '\"';
		if (quote)
		{
			j++;
			while (quote && str[j] != quote)
				push_char(word, str[j++]);
			j++;
		}
		else
			push_char(word, str[j++]);
	}
}

char	*get_word(char	*str, int *i, t_context *context)
{
	char	*word;
	int		len;

	word = safe_calloc(sizeof(char));
	avoid_spaces(str, i);
	len = get_word_len(str, *i);
	str = ft_substr(str, *i, len);
	*i += len;
	len = expand(&str, context);
	fill_word(len, str, &word);
	free(str);
	return (word);
}
