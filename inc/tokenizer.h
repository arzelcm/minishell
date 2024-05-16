#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "token.h"

t_token	*tokenize(char *line);
void	free_token(t_token *token);

#endif