#include "shell.h"

void process_command(const char *command); 

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 10

void process_command(const char *command)
{
	char *args[MAX_ARGUMENTS];

	// Tokenize the command 
	int argc = 0;
	char *token = strtok(command, " \t\n");
	while (token != NULL)
	{
		args[argc] = token; 
		token = strtok(NULL, "\t\n");
		argc++;

		if (argc >= MAX_ARGUMENTS)
		{
			char message[] = "Too many arguments. Maximum allowed is 10\n";
			write(STDERR_FILENO, message, strlen(message));
			return;
		}
	
	}
	
	if (argc == 0)
	{
		return;
	}

	args[argc] = NULL; 

	// Fork a child process
	
	pid_t pid =  fork();

	if (pid < 0) 
	{
		perror("Fork failed"); 
		exit(1);
	}
	else if (pid == 0)
	{
		// Child process: execute the command
		

	}
	
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		// Interactive mode 
		char input[MAX_COMMAND_LENGTH];
		ssize_t bytes_read;

		while (1) 
		{
			char prompt[] = "($) ";
			write(STDOUT_FILENO, prompt, strlen(prompt));

			bytes_read = read(STDIN_FILENO, input, sizeof(input) - 1);
			if (bytes_read == -1)
			{
				perror("Error reading from stdin");
				exit(1);
			}

			if (bytes_read == 0)
			{
				// Endd of input (e.g., when user presses Ctrl+D)
				break;
			}

			input[bytes_read] = '\0'; // Null-terminate the string

			process_command(input);
			
		}
	}

	return 0;
}

