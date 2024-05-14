#include "libft.h"
#include "lexer.h"

int	is_redirection(char *line, int index)
{
	return (line[index] == INPUT_RD[0]
		|| line[index] == OUTPUT_RD[0]
		|| (line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0])
		|| (line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0]));
}

void	throw_syntax_error(t_context *context, char *metachars)
{
	ft_printff(STDERR_FILENO, \
		"amethyst: syntax error near unexpected token `%s'\n", metachars);
	context->err_code = SYNTAX_ERROR;
}

int	check_metachar(t_context *context, char *line, int i)
{
	if (line[i] == PIPE[0])
		return (throw_syntax_error(context, PIPE), 0);
	else if (line[i] == INPUT_RD[0] && line[i + 1] == INPUT_RD[0])
		return (throw_syntax_error(context, HERE_DOC_RD), 0);
	else if (line[i] == OUTPUT_RD[0] && line[i + 1] == OUTPUT_RD[0])
		return (throw_syntax_error(context, APPEND_RD), 0);
	else if (line[i] == INPUT_RD[0])
		return (throw_syntax_error(context, INPUT_RD), 0);
	else if (line[i] == OUTPUT_RD[0])
		return (throw_syntax_error(context, OUTPUT_RD), 0);
	return (1);
}
