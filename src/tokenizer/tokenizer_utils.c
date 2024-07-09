/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:59:29 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/10 00:03:55 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_utils.h"
#include "libft.h"
#include "utils.h"
#include "expansor.h"
#include "quotes_utils.h"
#include "tokenizer.h"

int	get_raw_word_len(char *str, int i)
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

int	get_word_len(char *str, int i)
{
	int	start_i;
	int	is_quoted;

	start_i = i;
	is_quoted = (str[i] == '\'' || str[i] == '"');
	if (str[i] == '$')
		i++;
	if (i > 0 && str[i] == '$' && str[i - 1] == '$')
		return (2);
	while (str[i] != '\0' && str[i] != '$')
	{
		if (is_quoted)
		{
			avoid_quotes(str, &i);
			break ;
		}
		else if (str[i] == '\'' || str[i] == '"')
			break ;
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

char	*get_word(char *str, int *i, t_context *context, t_expansion *expansion)
{
	char			*word;
	int				len;
	t_quotes_flag	quotes;

	ft_bzero(&quotes, sizeof(t_quotes_flag));
	if (expansion)
		ft_bzero(expansion, sizeof(t_expansion));
	avoid_spaces(str, i);
	if (str[*i] == '$' && *i + 1 < (int) ft_strlen(str)
		&& (str[*i + 1] == '\'' || str[*i + 1] == '"'))
		(*i)++;
	check_quotes(&quotes, str[*i]);
	if (expansion)
		expansion->quoted = quotes.double_;
	len = get_word_len(str, *i);
	word = safe_ft_substr(str, *i, len, syserr);
	*i += len;
	str = safe_ft_strdup("", syserr);
	fill_word(len, word, &str);
	free(word);
	if (!quotes.simple)
		expand(&str, context, expansion);
	return (str);
}

char	*get_raw_word(char	*str, int *i)
{
	char	*word;
	int		len;

	avoid_spaces(str, i);
	len = get_raw_word_len(str, *i);
	word = safe_ft_substr(str, *i, len, syserr);
	*i += len;
	return (word);
}
