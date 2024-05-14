#include "libft.h"
#include "lexer.h"
#include "lexer_utils.h"
#include "meta_chars.h"

static void	check_quotes(t_meta_flags *flags, char c)
{
	if (c == D_QUOTE[0] && !flags->s_quote)
		flags->d_quote = !flags->d_quote;
	else if (c == S_QUOTE[0] && !flags->d_quote)
		flags->s_quote = !flags->s_quote;
}

static int	check_pipe(t_context *context, char *line, int index)
{
	int	i;

	if (line[index] != PIPE[0])
		return (1);
	i = index - 1;
	while (i >= 0)
	{
		if (line[i] != ' ')
			break ;
		i--;
	}
	if (i < 0)
		return (throw_syntax_error(context, PIPE), 0);
	i = index + 1;
	while (line[i])
	{
		if (line[i] == PIPE[0])
			return (throw_syntax_error(context, PIPE), 0);
		else if (line[i] != ' ')
			break ;
		i++;
	}
	if (line[i] == '\0')
		return (throw_syntax_error(context, "newline"), 0);
	return (1);
}

static int	check_redirection(t_context *context, char *line, int index)
{
	int	i;

	if (!is_redirection(line, index))
		return (1);
	i = index + 1;
	if ((line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0]) 
		|| (line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0]))
		i++;
	while (line[i])
	{
		if (!check_metachar(context, line, i))
			return (0);
		else if (line[i] != ' ')
			break ;
		i++;
	}
	if (line[i] == '\0')
		return (throw_syntax_error(context, "newline"), 0);
	return (1);
}

int	check_syntax(t_context *context, char *line)
{
	t_meta_flags	flags;
	int				i;

	ft_bzero(&flags, sizeof(t_meta_flags));
	i = 0;	
	while (line[i])
	{
		check_quotes(&flags, line[i]);
		if (!flags.d_quote && !flags.s_quote && !check_pipe(context, line, i))
			return (0);
		if (!flags.d_quote && !flags.s_quote
			&& !check_redirection(context, line, i))
			return (0);
		i++;
	}
	if (flags.d_quote)
		return (throw_syntax_error(context, D_QUOTE), 0);
	else if (flags.s_quote)
		return (throw_syntax_error(context, S_QUOTE), 0);
	return (1);
}
