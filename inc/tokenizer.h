#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "token.h"
# include "context.h"

t_token	*tokenize(char *line, t_context *context);

void	free_args(char **args);

int		set_definitions(char *line, int *i,
			t_context *context, t_token **token);

#endif