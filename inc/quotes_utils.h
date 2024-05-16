#ifndef QUOTES_UTILS_H
# define QUOTES_UTILS_H

# include "quotes_flag.h"

void	check_quotes(t_quotes_flag *quotes, char c);

int	avoid_quotes(char *str, int *i);

#endif