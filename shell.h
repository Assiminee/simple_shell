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

extern char **environ;
/**
 * struct builtins - struct builtins
 * @func_name: pointer to char
 * @f: pointer function
 */
typedef struct builtins
{
	char *func_name;
	void (*f)(char **av, char **user_input);
} builtins;

void free_ptr(char **args);
int num_elements(char *line);
int tokenize(char ***args, char **line);
int elements(char **tokenized);
char *_getenv(const char *name);
char *return_value(const char *entry);
char *find_path_to_file(char *fileName);
int is_path(char *string);
void error_message(char *command, char *message);
size_t _strlen(const char *string);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *string);
char *_strcat(char *dest, const char *src);
char *_strchr(char *p, const char ch);
char *_strtok(char *str, const char *delim);
int _strncmp(const char *s1, const char *s2, size_t n);
void execute_commands(char **av, char *env[], char **user_input);
int check_existance(char **av, char **user_input);
char *extract_command(char *path);
int contains_char(char *string, char character);
void exit_bul(char **av, char **user_input);
int _strcmp(const char *s1, const char *s2);
int print_to_console(char *string);
void remove_space(char **user_input);
void prompt(void);
void fork_error(char **av, char **user_input, pid_t pid);
void env_bul(char **av, char **user_input);
int exe_builtins(char **av, char **user_input);

#endif
