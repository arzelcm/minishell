#include "libft.h"
#include "lexer_utils.h"

void	throw_syntax_error(t_context *context, char *metachars)
{
	ft_printff(STDERR_FILENO, \
		"amethyst: syntax error near unexpected token `%s'\n", metachars);
	context->err_code = SYNTAX_ERROR;
}
