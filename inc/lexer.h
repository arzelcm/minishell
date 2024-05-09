#ifndef LEXER_H
# define LEXER_H
# define D_QUOTE "\""
# define S_QUOTE "\'"
# include "context.h"

typedef struct s_meta_flags
{
	int	double_quote;
	int	single_quote;
}	t_meta_flags;

int	check_syntax(t_context *context, char *line);

#endif
