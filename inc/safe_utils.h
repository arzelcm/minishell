#ifndef SAFE_UTILS_H
# define SAFE_UTILS_H

# include <stddef.h>

void	*safe_calloc(size_t size);

void	safe_close(int *fd);

#endif