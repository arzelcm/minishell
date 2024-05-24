#include "safe_utils.h"
#include "utils.h"
#include "libft.h"
#include "executor_utils.h"
#include "open_utils.h"

int	open_here_docs(t_redirection *infiles, int here_docs_amount)
{
	int				i;
	int				fd;
	t_redirection	*file;

	i = 0;
	fd = -1;
	file = infiles;
	while (file && i < here_docs_amount)
	{
		if (file->mode == HERE_DOC)
		{
			fd = open_here_doc(file);
			i++;
		}
		if (i != here_docs_amount)
			safe_close(&fd);
		file = file->next;
	}
	return (fd);
}

int	open_infiles(int read_fd, t_redirection *infiles, int here_docs_amount)
{
	int				i;
	int				failed;
	t_redirection	*file;

	i = 0;
	failed = 0;
	file = infiles;
	while (file)
	{
		if (file->mode != HERE_DOC)
			failed += open_next_infile(file, i, &read_fd, here_docs_amount);
		else
			i++;
		file = file->next;
	}
	if (failed)
		safe_close(&read_fd);
	return (read_fd);
}

int	open_outfiles(int write_fd, t_redirection *outfiles)
{
	int				fd;
	int				failed;
	t_redirection	*file;

	fd = write_fd;
	file = outfiles;
	failed = 0;
	while (file)
	{
		fd = open_outfile(file->path, file->mode);
		if (fd == -1)
			failed++;
		if (file->next)
			safe_close(&fd);
		file = file->next;
	}
	if (failed)
		safe_close(&fd);
	return (fd);
}
