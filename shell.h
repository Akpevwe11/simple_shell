#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

extern char **environ;

/* for command chaining */
#define CMD_OR '1'
#define CMD_AND '2'
#define SEMICOLON '3'
#define CMD_PIPE '4'
#define REOUTDOBLE '5'
#define REOUT '6'
#define REIN   '7'
#define REINDOBLE  '8'
#define COMMENT  '9'

#define READ 0	/* index for the pipe's write end */
#define WRITE 1 /* index for the pipe's read end */

/**
 *struct passinfo - contains *
 * @err_num: the error code for exit()s
 * @readfd: the fd from which to read line input
 * @startup_fd: fd of startup file or -1
 * @flaqs: flaqs for identify delimiters
 * @numberflaqs: number of flaqs
 * @status: status of child
 * @pipefd: pipe1
 * @argv: args
 * @path: path to use with execve
 * @tokens: tokens cut for space
 * @write_inPipe: flaqs used in pipe
 * @read_inPipe: flaqs used in pipe
 * @filename: name of file to out redirection
 * @redirfilefd: fd of file to write redirection
 * @redirfilefd2: fd of file to read redirection
 * @dup_stdin: copy stdin
 * @dup_stdout: copy stdout
 * @count: count errors
 * @fname: name execute file
 * @ident: identify flaq redirections
 * @identcomment: flaq comments
 * @condition: flaq stop shell
 * @dup_stderr: save state STDERR
 */
typedef struct passinfo
{
	int err_num;
	int readfd;
	int startup_fd;
	char flaqs[21];
	int numberflaqs;
	int status;
	int pipefd[2];
	char **argv;
	char *path;
	char **tokens;
	int write_inPipe;
	int read_inPipe;
	char *filename;
	int redirfilefd;
	int redirfilefd2;
	int dup_stdin;
	int dup_stdout;
	int count;
	char *fname;
	int ident;
	int identcomment;
	int condition;
	int dup_stderr;
} info_t;

#define INFO_INIT                                                    \
	{0, 0, -1, {0}, 0, 0, {0}, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0, \
	0, 0, NULL, 0, 0, 1, 0}

int main(int argc, char **argv);
void _eputs(char *str);
int _eputchar(char c);
int open_file(info_t *info, char *name, int silent);
void free_info(info_t *info, int all);
char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);


/* Auxiliar Prototypes */
int _putchar(char c);
int _strlen(char *s);
int _strtoken(char **tokens);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void redireccion(info_t *info);
void restore_std_in_out(info_t *info);

/* PATH */
void find_cmd(info_t *info);
char *find_path(info_t *info, char *pathstr, char *cmd);
char *starts_with(const char *string, const char *findstr);
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);

/* Environ */
extern char **environ;
int _unsetenv(info_t *info, char **tokens);
int _setenv(info_t *info, char **tokens);

#endif
