#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "token.h"

t_token	*tokenize(char *line);

void	free_args(char **args);

#endif