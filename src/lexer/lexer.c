#include "libft.h"
#include "lexer.h"
#include "lexer_utils.h"

static void	check_quotes(t_meta_flags *flags, char c)
{
	if (c == D_QUOTE[0] && !flags->single_quote)
		flags->double_quote = !flags->double_quote;
	else if (c == S_QUOTE[0] && !flags->double_quote)
		flags->single_quote = !flags->single_quote;
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
		i++;
	}
	if (flags.double_quote)
		return (throw_syntax_error(context, D_QUOTE), 0);
	else if (flags.single_quote)
		return (throw_syntax_error(context, S_QUOTE), 0);
	return (1);
}
