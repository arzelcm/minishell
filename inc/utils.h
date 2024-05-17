#ifndef CUSTOM_UTILS_H
# define CUSTOM_UTILS_H

# include "quotes_flag.h"

void	custom_exit(int exit_code);

void	check_quotes(t_quotes_flag *quotes, char c);

void	handle_syserror(int errnum);

void	handle_error(char *file, char *message);

char	*quote_str(char *str);

#endif