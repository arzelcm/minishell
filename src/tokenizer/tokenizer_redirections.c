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
	ft_printf("path: %s\n", path);
	if (mode == HERE_DOC)
		token->here_docs++;
	if (mode == HERE_DOC || mode == INPUT)
		current = &token->infiles;
	else
		current = &token->outfiles;
	if (!*current)
	{
		*current = new_redirection(mode, path);
		return ;
	}
	while ((*current)->next)
		*current = (*current)->next;
	(*current)->next = new_redirection(mode, path);
}

// static char	*get_red_filename(char *line, int *i, t_redirection_mode mode, t_context *context)
// {
// 	int					expanded;
// 	int					quoted;
// 	char				*word;
// 	int					start;

// 	expanded = 0;
// 	quoted = 0;
// 	avoid_spaces(line, i);
// 	start = *i;
// 	if (mode == HERE_DOC)
// 		word = get_word(line, i, NULL, NULL, NULL);
// 	else
// 		word = get_word(line, i, NULL, NULL, NULL);
// 	if (expanded && !quoted && (ft_stroccurrences(word, ' ') || !*word))
// 	{
// 		handle_error(line + start, "ambiguous redirect");
// 		context->err_code = EXIT_FAILURE;
// 		free(word);
// 		return (NULL);
// 	}
// 	return (word);
// }

int	set_redirection(char *line, int *i, t_token *token)
{
	int					start_i;
	t_redirection_mode	mode;

	start_i = *i;
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
	return (*i > start_i);
}
