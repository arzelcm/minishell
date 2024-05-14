#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H
# include "context.h"

int		is_redirection(char *line, int index);

void	throw_syntax_error(t_context *context, char *metachars);

int		check_metachar(t_context *context, char *line, int i);

#endif
