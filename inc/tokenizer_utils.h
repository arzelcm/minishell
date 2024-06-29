#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

# include "context.h"
# include "expansor.h"

int		avoid_spaces(char *str, int *i);

char	*get_word(char	*str, int *i, t_context *context,
			t_expansion *expansion);

char	*get_raw_word(char	*str, int *i);

#endif