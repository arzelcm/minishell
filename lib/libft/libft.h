/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:00:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/07/06 18:26:33 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "get_next_line.h"
# include "ft_printf.h"
# include "ft_strncmp.h"

int			ft_isalpha(int c);

int			ft_isdigit(int c);

int			ft_isnum(char *str, long long max, long long min);

int			ft_isalnum(int c);

int			ft_isascii(int c);

int			ft_isprint(int c);

size_t		ft_strlen(const char *s);

void		*ft_memset(void *b, int c, size_t len);

void		ft_bzero(void *s, size_t n);

void		*ft_memcpy(void *dst, const void *src, size_t n);

void		*ft_memmove(void *dst, const void *src, size_t len);

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);

int			ft_toupper(int c);

int			ft_tolower(int c);

char		*ft_strchr(const char *s, int c);

char		*ft_strrchr(const char *s, int c);

void		*ft_memchr(const void *s, int c, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

char		*ft_strrstr(const char *haystack, const char *needle);

int			ft_atoi(const char *str);

long		ft_atol(const char *str);

long long	ft_atoll(const char *str);

void		*ft_calloc(size_t count, size_t size);

char		*ft_strdup(const char *s1);

char		*ft_substr(char const *s, unsigned int start, size_t len);

char		*ft_strjoin(char const *s1, char const *s2);

char		*ft_strtrim(char const *s1, char const *set);

char		**ft_split_set(char const *s, char const *set);

char		**ft_split(char const *s, char c);

char		*ft_itoa(int n);

char		*ft_ltoa(long n);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_striteri(char *s, void (*f)(unsigned int, char*));

void		ft_putchar_fd(char c, int fd);

int			ft_putchar(int fd, const char *c, int *counter);

void		ft_putstr_fd(char *s, int fd);

void		ft_putendl_fd(char *s, int fd);

void		ft_putnbr_fd(int n, int fd);

void		free_matrix(char **space);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lstnew(void *content);

void		ft_lstadd_front(t_list **lst, t_list *new);

int			ft_lstsize(t_list *lst);

t_list		*ft_lstlast(t_list *lst);

void		ft_lstadd_back(t_list **lst, t_list *new);

void		ft_lstdelone(t_list *lst, void (*del)(void*));

void		ft_lstclear(t_list **lst, void (*del)(void*));

void		ft_lstiter(t_list *lst, void (*f)(void *));

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int			ft_putstr(int fd, char *str, int *count);

long		ft_putnbr(int fd, long n, int *count);

int			count_digits(long nbr);

int			count_ull_digits(unsigned long long nbr);

int			count_hex_digits(unsigned int nbr);

char		*ft_filename(char *path);

int			ft_stroccurrences(char *str, char c);

int			ft_stroccurrences_set(char *str, char *set);

int			ft_normalize(int value, int min, int max);

long		ft_closest_multiple(long n, long x);

void		ft_matrix_sort(char **matrix);

char		*safe_ltoa(long n);

long		get_positive_num(int n);

char		*safe_ft_strdup(const char *s1, void (*f)(int));

char		*safe_ft_strjoin(char const *s1, char const *s2, void (*f)(int));

char		*safe_ft_substr(char const *s, unsigned int start,
				size_t len, void (*f)(int));

#endif
