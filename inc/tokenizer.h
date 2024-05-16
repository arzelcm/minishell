#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "token.h"
# include "context.h"

t_token	*tokenize(char *line, t_context *context);

void	free_args(char **args);

#endif