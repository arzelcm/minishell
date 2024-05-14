#ifndef LEXER_H
# define LEXER_H
# include "context.h"

typedef struct s_meta_flags
{
	int	d_quote;
	int	s_quote;
}	t_meta_flags;

int	check_syntax(t_context *context, char *line);

#endif
