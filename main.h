#ifndef MAIN_H
#define MAIN_H

/*--------- <libraries>------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>


/**
 *struct list_path- linked list containing path directories.
 *@dir: name of the directory.
 *@next_node: pointer to the node.
 */
typedef struct list_path
{
	char *dir;
	struct list_path *next_node;
} list_path;

/**
 *struct built_in - struct to built in commands and the corresponding function
 *@name: built in command
 *@func: corresponding function
 */
typedef struct built_in
{
	char *name;
	void (*func)(char **);
} built_in;

/* -----------------< functions in built_in.c>------------------------------ */

int exit_status;
char *shell_name;
void _cd(char **command);
void _env(__attribute__((unused)) char **command);
void _exit_(char **command);
void _setenv(char **command);
void _unsetenv(char **command);

/* -------------------< functions in execute.c >---------------------------- */

int built_in_handler(char **builtin);
void execute(char **command, char *envp[]);
char *_which(char *file_name);

/* -------------------< functions in write.c >------------------------------ */

int _puts(char *str, int stream);
void _perror(char *command, char *str);
void _perror_cd(char **command);
void _isatty(void);
void sig_handler(int sig);

/* -------------------< functions in directories_list.c >------------------- */

extern char **environ;

list_path *add_node_end(list_path **head, const char *str);
list_path *list_path_directory(void);
void free_list(list_path *head);

/* -------------------< functions in env_list.c >--------------------------- */

/**
 * struct list_env - linked list containing environment
 * @name: name of environment
 * @value: value of environment
 * @next_env: pointer to the next node
 */
typedef struct list_env
{
	char *name;
	char *value;
	struct list_env *next_env;
} list_env;

list_env *env_head;

list_env *add_env_end(char *str);
list_env *list_environment(char *envp[]);
void free_list_env(void);
void _printenv(void);

/* -------------------< functions in env.c >-------------------------------- */

char *_getenv(const char *var_name);
int set_env(const char *name, const char *value, int overwrite);
int unset_env(const char *name);

/* ------------------< functions in string_parse.c >------------------------ */

char **string_parse(char *str, char *delim, int num_token);
void *_realloc(void *ptr, int new_size);

/* ----------------< functions in string.c >-------------------------------- */

int _atoi(const char *s);
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *str);
char *str_concat(const char *s1, const char *s2);

#endif
