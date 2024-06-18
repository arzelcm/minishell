#ifndef TOKENIZER_REDIRECTIONS_H
# define TOKENIZER_REDIRECTIONS_H

# include "token.h"
# include "context.h"

void	free_redirections(t_redirection *list);

int		set_redirection(char *line, int *i, t_token *token);

#endif