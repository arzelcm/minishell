#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

int		is_directory(char *path);

int		check_cmd(char *cmd);

void	check_bin(char *bin);

char	*join_full_path(char *path, char *cmd);

#endif
