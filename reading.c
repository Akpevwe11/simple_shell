#include "shell.h"

/**
 * reading - Read a line of text from standard input. 
 *
 * Description:
 *  This function reads a line of text from the standard input (stdin) and 
 *  dynamically allocates memory to store the input line. The allocated memeory
 *  is managed by the caller and should be freed when no longer needed.
 *
 * Return: 
 *  On successful input, the function returns a dynamically allocated char
 *  pointer containing the read line. The caller is responsible for freeing this memory
 *  if an error occurs or the end of the input is reached, the function frees
 *  any allocated memory and exits the program with a status code of 0
 */

char *reading(void)
{
	char *line = NULL;
	size_t buff_size = 0;
	ssize_t bytes_read = 0; 

	bytes_read = getline(&line, &buff_size, stdin);
	if(bytes_read == -1)
		free(line),exit(0);
	return (line);
}
