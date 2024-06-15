#include "safe_utils.h"
#include "libft.h"
#include "utils.h"
#include "expansor.h"
#include "quotes_utils.h"

int	avoid_spaces(char *str, int *i)
{
	if (str[*i] != ' ' && str[*i] != '\t')
		return (0);
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	return (1);
}

int	get_word_len(char *str, int i)
{
	int	start_i;

	start_i = i;
	while (str[i] != '\0' && !ft_stroccurrences("| \t<>", str[i]))
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

char	*get_word(char	*str, int *i, t_context *context, int *expanded, int *quoted)
{
	char	*word;
	int		len;
	int		word_len;

	word = safe_calloc(sizeof(char));
	avoid_spaces(str, i);
	word_len = get_word_len(str, *i);
	len = word_len;
	str = ft_substr(str, *i, len);
	*i += len;
	if (context)
		len = expand(&str, context, expanded, quoted);
	fill_word(len, str, &word);
	free(str);
	return (word);
}
