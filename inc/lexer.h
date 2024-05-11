#ifndef LEXER_H
# define LEXER_H
# define D_QUOTE "\""
# define S_QUOTE "\'"
# define PIPE "|"
# define INPUT_RD "<"
# define OUTPUT_RD ">"
# define HERE_DOC_RD "<<"
# define APPEND_RD ">>"
# include "context.h"

typedef struct s_meta_flags
{
	int	d_quote;
	int	s_quote;
}	t_meta_flags;

int	check_syntax(t_context *context, char *line);

#endif
