#include "shell.h"
/**
 * main -This function serves as the main entry point for the program
 * @argc: The count of command - command line arguments.
 * @argv: an array of strings containing commandline arguments.
 * Return: Integer representing the exit status of the program - 0: the program executed successfully
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	char **lines = NULL;
	info_t info[] = {INFO_INIT};
	int flaqread = 0;

	info->fname = argv[0];
	if (argc == 2)
	{
		info->readfd = open_file(info, argv[1], 0);
		if (info->readfd == -1)
			exit(info->err_num);
		else
			flaqread = 1;
	}
	signal(SIGINT, sigint_handler);
	while (info->condition)
	{
		if (flaqread == 1)
		{
			line = __getline(info->readfd);
			if (!line)
				break;
		}
		else
		{
			write(STDIN_FILENO, "($) ", 4);
			line = reading();
		}
		identifydelim(info, line);
		lines = cutting(line);
		checkone(info, lines);
		restore_std_in_out(info);
		free(line);
		free(lines);
	}
	return (EXIT_SUCCESS);
}
