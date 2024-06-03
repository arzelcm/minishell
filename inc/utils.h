#ifndef UTILS_H
# define UTILS_H

# include "context.h"

void	custom_exit(int exit_code);

void	c_exit(t_context *context);

void	push_char(char	**str, char c);

void	handle_syserror(int errnum);

void	handle_error(char *file, char *message);

char	*quote_str(char *str);

#endif