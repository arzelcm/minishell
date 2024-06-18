#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

# include "context.h"

int		avoid_spaces(char *str, int *i);

char	*get_word(char	*str, int *i, t_context *context, int *expanded, int *quoted);

char	*get_raw_word(char	*str, int *i, int keep_quotes);

#endif