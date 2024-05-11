#include "libft.h"
#include "lexer.h"
#include "lexer_utils.h"

int	is_redirection(char *line, int index)
{
	if (line[index] == INPUT_RD[0]
		|| line[index] == OUTPUT_RD[0]
		|| (line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0])
		|| (line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0]))
		return (1);
	return (0);
}

void	throw_syntax_error(t_context *context, char *metachars)
{
	ft_printff(STDERR_FILENO, \
		"amethyst: syntax error near unexpected token `%s'\n", metachars);
	context->err_code = SYNTAX_ERROR;
}
