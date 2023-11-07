#include "shell.h"

/**
 * open_file - opens a file descriptor, exits on failure
 * @info: Pointer to the parater struct
 * @name: Name of the file to open
 * @silent: Flag to control error message printing (0 for printing, 1 for silent)
 *
 * Return: File descriptor of the opened file on success, or -1 on failure.
 */

int open_file(info_t *info, char *name, int silent)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd == -1 && !silent)
	{
		if (errno == EACCES)
			info->err_num = 126;
		if (errno == ENOENT)
		{
			_eputs("./hsh");
			_eputs(": 0: Can't open ");
			_eputs(name);
			_eputchar('\n');
			_eputchar(BUF_FLUSH);
			info->err_num = 127;
		}
		return (-1);
	}
	return (fd);
}
