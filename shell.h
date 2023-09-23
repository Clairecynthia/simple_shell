#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@eva: linked list local copy of environ
 *@eva: custom modified copy of eva from LL env
 *@history: the history node
 *@alias: the alias node
 *@eva_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} params_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct custom - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct custom
{
	char *type;
	int (*func)(params_t *);
} custom_table;


/* ourhsh.c */
int ourhsh(char **, params_t *);
int find_custom(params_t *);
void find_command(params_t *);

/* ourhsh2.c */
void fork_command(params_t *);

/* find_path.c */
int is_command(char *, params_t *);
char *dup_chars(char *, int, int);
char *locate_path(char *, char *, params_t *);

/* loophsh.c */
int loophsh(char **);

/* e_string_func.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* shell_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *begin_with(const char *, const char *);
char *_strcat(char *, char *);

/* shell_string2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* shell_string3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* shell_string4.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* storage_allocation.c */
char *_memset(char *, char, unsigned int);
void release_string_array(char **);
void *custom_realloc(void *, unsigned int, unsigned int);
int free_and_null(void **);


/* builtin_emulators.c */
int _myexit(params_t *);
int _mycd(params_t *);
int _myhelp(params_t *);

/* builtin_emulators2.c */
int _myhistory(params_t *);
int _myalias(params_t *);

/* getline.c module */
ssize_t get_input(params_t *);
int _getline(params_t *, char **, size_t *);
void sigintHandler(int);

/* eva.c  */
char *_geteva(params_t *, const char *);
int _myeva(params_t *);
int _myseteva(params_t *);
int _myunseteva(params_t *);
int populate_eva_list(params_t *params);

/* eva2.c */
char **get_eva2(params_t *params);
int _unseteva(params_t *, char *);
int _seteva(params_t *, char *, char *);


/* builtin_command.c */
int _isexit(params_t *);
int _iscd(params_t *);
int _ishelp(params_t *);

/* alias.c */
int _ishistory(params_t *);
int unset_alias(char *, params_t *);
int set_alias(char *, params_t *);
int _isalias(params_t *);

/* my_getline.c */
ssize_t get_input(params_t *);
ssize_t read_buf(char *, size_t *, params_t *);
ssize_t input_buf(char **, size_t *, params_t *);
int _getline(char **, size_t *, params_t *);
void sigintHandler(int);

/* io-params.c */
char *get_history_file(params_t *params);
int write_history(params_t *params);
int read_history(params_t *params);
int build_history_list(params_t *params, char *buf, int linecount);
int renumber_history(params_t *params);


/* nan.c */
int is_nan(params_t *, char *, size_t *);
void check_chain(params_t *, char *, size_t *, size_t, size_t);
int replace_alias(params_t *);
int replace_vars(params_t *);
int replace_string(char **, char *);

#endif
