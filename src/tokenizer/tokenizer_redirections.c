#include "libft.h"
#include "utils.h"
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
	push_redirection(t_redirection_mode mode, char *path, t_token *token)
{
	t_redirection	**current;

	if (!path || mode == UNKNOWN_RED)
		return ;
	if (mode == HERE_DOC)
		token->here_docs++;
	current = &token->redirections;
	if (mode == HERE_DOC || mode == INPUT)
		token->infiles++;
	else
		token->outfiles++;
	if (!*current)
	{
		*current = new_redirection(mode, path);
		return ;
	}
	while ((*current)->next)
		*current = (*current)->next;
	(*current)->next = new_redirection(mode, path);
}

int	set_redirection(char *line, int *i, t_token *token)
{
	t_redirection_mode	mode;

	mode = UNKNOWN_RED;
	if (line[*i] == '<' && line[*i + 1] == '<')
		mode = HERE_DOC;
	else if (line[*i] == '<')
		mode = INPUT;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		mode = APPEND;
	else if (line[*i] == '>')
		mode = OUTPUT;
	if (mode == HERE_DOC || mode == APPEND)
		(*i) += 2;
	else if (mode == INPUT || mode == OUTPUT)
		(*i)++;
	if (mode != UNKNOWN_RED)
		push_redirection(mode, get_raw_word(line, i, 1), token);
	return (mode != UNKNOWN_RED);
}

char	*expand_redirect(t_redirection *redirection, t_context *context)
{

	int					expanded;
	int					quoted;
	char				*word;
	int					i;

	expanded = 0;
	quoted = 0;
	i = 0;
	avoid_spaces(redirection->path, &i);
	if (redirection->mode == HERE_DOC)
		word = get_raw_word(redirection->path, &i, 0);
	else
		word = get_word(redirection->path, &i, context, &expanded, &quoted);
	if (expanded && !quoted && (ft_stroccurrences(word, ' ') || !*word))
	{
		handle_error(redirection->path, "ambiguous redirect");
		context->err_code = EXIT_FAILURE;
		free(word);
		return (NULL);
	}
	free(redirection->path);
	redirection->path = word;
	return (redirection->path);
}
