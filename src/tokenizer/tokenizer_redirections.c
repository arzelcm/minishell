#include "token.h"
#include "tokenizer_utils.h"
#include "safe_utils.h"
#include <stdlib.h>

static void	free_redirection(t_redirection *redirection)
{
	free(redirection->path);
	free(redirection);
}

void	free_redirections(t_redirection *list)
{
	t_redirection	*aux;

	while (list)
	{
		aux = list;
		list = list->next;
		free_redirection(aux);
	}
}

t_redirection	*new_redirection(t_redirection_mode mode, char *path)
{
	t_redirection	*redirection;

	redirection = safe_calloc(sizeof(t_redirection));
	redirection->mode = mode;
	redirection->path = path;
	return (redirection);
}

void
	push_redirection(t_redirection_mode mode, char *path, t_redirection **list)
{
	t_redirection	*current;

	current = *list;
	if (!current)
	{
		*list = new_redirection(mode, path);
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new_redirection(mode, path);
}

int	set_redirection(char *line, int *i, t_token *token)
{
	int	start_i;

	start_i = *i;
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*i) += 2;
		push_redirection(HERE_DOC, get_word(line, i), &token->infiles);
		token->here_docs++;
	}
	else if (line[*i] == '<')
	{
		(*i)++;
		push_redirection(INPUT, get_word(line, i), &token->infiles);
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*i) += 2;
		push_redirection(OUTPUT_APPEND, get_word(line, i), &token->outfiles);
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		push_redirection(OUTPUT, get_word(line, i), &token->outfiles);
	}
	return (*i > start_i);
}
