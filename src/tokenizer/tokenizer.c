#include "libft.h"
#include "safe_utils.h"
#include "token.h"
#include "quotes_flag.h"
#include "quotes_utils.h"
#include "tokenizer_utils.h"

void	free_redirection(t_redirection *redirection)
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

void	free_args(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_token(t_token *token)
{
	free_redirections(token->infiles);
	free_redirections(token->outfiles);
	free_args(token->args);
	free(token);
}

t_token	*new_token(t_token_type type)
{
	t_token	*token;

	token = safe_calloc(sizeof(t_token));
	token->type = type;
	return (token);
}

void	print_token(t_token *token)
{
	t_redirection	*aux;
	int				i;
	ft_printf("token: %p (%i)\n", token, token->type);
	ft_printf("args: ", token, token->type);
	i = 0;
	while (token->args[i])
	{
		ft_printf("%s, ", token->args[i]);
		i++;
	}
	ft_printf("\ninfiles: ");
	aux = token->infiles;
	while (aux)
	{
		ft_printf("%s, ", aux->path);
		aux = aux->next;
	}
	ft_printf("\noutfiles: ");
	aux = token->outfiles;
	while (aux)
	{
		ft_printf("%s, ", aux->path);
		aux = aux->next;
	}
	ft_printf("\nhere_docs: %i\n", token->here_docs);
}

void	push_char(char	**str, char c)
{
	char	*new_word;
	int		len;

	len = ft_strlen(*str);
	new_word = safe_calloc(sizeof(char) * (len + 2));
	ft_strlcpy(new_word, *str, -1);
	new_word[len] = c;
	new_word[len + 1] = '\0';
	free(*str);
	*str = new_word;
}

char	*get_word(char	*str, int *i)
{
	char	*word;
	char	quote;

	word = safe_calloc(sizeof(char));
	avoid_spaces(str, i);
	while (str[*i] != '\0' && !ft_stroccurrences("| <>&", str[*i]))
	{
		quote = '\0';
		if (str[*i] == '\'')
			quote = '\'';
		else if (str[*i] == '\"')
			quote = '\"';
		if (quote)
		{
			(*i)++;
			while (quote && str[*i] != quote)
				push_char(&word, str[(*i)++]);
			(*i)++;
		}
		else
			push_char(&word, str[(*i)++]);
	}
	return (word);
}

t_redirection	*new_redirection(t_redirection_mode mode, char *path)
{
	t_redirection	*redirection;

	redirection = safe_calloc(sizeof(t_redirection));
	redirection->mode = mode;
	redirection->path = path;
	return (redirection);
}

void	push_redirection(t_redirection_mode mode, char *path, t_redirection **list)
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

void	push_arg(char ***args, char *new_arg)
{
	char	**new;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (*args && (*args)[i])
		i++;
	len = i;
	new = safe_calloc(sizeof(char *) * (len + 2));
	i = -1;
	while (++i < len)
		new[i] = (*args)[i];
	new[len] = new_arg;
	new[len + 1] = NULL;
	free(*args);
	*args = new;
}

int	set_pipe()
{
	return (0);
}

t_token	*tokenize(char *line)
{
	t_token			*token;
	int				i;

	token = new_token(CMD);
	i = 0;
	while (line[i])
	{
		if (set_redirection(line, &i, token))
			continue ;
		if (set_pipe(line, &i, token))
			continue ;
		push_arg(&token->args, get_word(line, &i));
	}
	print_token(token);
	return (token);
}
