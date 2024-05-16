#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

# include "context.h"

void	avoid_spaces(char *str, int *i);

char	*get_word(char	*str, int *i, t_context *context);

#endif