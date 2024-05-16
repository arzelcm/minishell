void	avoid_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}