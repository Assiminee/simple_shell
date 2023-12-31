#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <dirent.h>

extern char **environ;
extern char *user_input;
extern char **env_vars;
/**
 * struct builtins - struct builtins
 * @func_name: pointer to char
 * @f: pointer function
 */
typedef struct builtins
{
	char *func_name;
	void (*f)(char **av, int status, char *shell_name);
} builtins;

void free_ptr(char **args);
int num_elements(char *line);
int tokenize(char ***args);
int elements(char **tokenized);
char *_getenv(const char *name);
char *return_value(const char *entry);
char *find_path_to_file(char *fileName);
int is_path(char *string);
void error_message(char *command, char *shell_name);
size_t _strlen(const char *string);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *string);
char *_strcat(char *dest, const char *src);
char *_strchr(char *p, const char ch);
char *_strtok(char *str, const char *delim);
int _strncmp(const char *s1, const char *s2, size_t n);
void execute_commands(char **av, char *env[]);
int check_existance(char **av, char *shell_name, int *status);
char *extract_command(char *path);
int contains_char(char *string, char character);
void exit_bul(char **av, int status, char *shell_name);
int _strcmp(const char *s1, const char *s2);
int print_to_console(char *string);
void remove_space(void);
void prompt(void);
void fork_error(char **av, pid_t pid);
void env_bul(char **av, int status, char *shell_name);
int exe_builtins(char **av, int status, char *shell_name);
int check_for_space(void);
int pre_execution(char ***av, int *status, char *shell_name);
void handleCtrlC(int signal);
int _atoi(char *s);
int valid_exit_arg(char *arg);
int exit_status(char *arg);
int env_cpy(void);
int num_env_vars(void);

/* setenv */
bool check_var(const char *name);
char *create_entry(const char *name, const char *value);
int _setenv(char *name, char *value);

/* unsetenv */
int _unsetenv(char **av);

/* cd */
void _cd(char *path, char *shell_name);
#endif
