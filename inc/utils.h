#ifndef UTILS_H
# define UTILS_H

void	custom_exit(int exit_code);

void	push_char(char	**str, char c);

void	handle_syserror(int errnum);

void	handle_error(char *file, char *message);

char	*quote_str(char *str);

#endif