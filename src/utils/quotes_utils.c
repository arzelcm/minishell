#include "quotes_flag.h"

void	check_quotes(t_quotes_flag *quotes, char c)
{
	if (c == '\'' && !quotes->double_)
		quotes->simple = !quotes->simple;
	else if (c == '\"' && !quotes->simple)
		quotes->double_ = !quotes->double_;
}

void	avoid_quotes(char *str, int *i)
{
	char	quote;

	if (str[*i] == '\"')
		quote = '\"';
	else if (str[*i] == '\'')
		quote = '\'';
	else
		return ;
	(*i)++;
	while (str[*i] != quote)
		(*i)++;
	(*i)++;
}