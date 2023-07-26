#include "shell.h"
/* TASK 3 */
/* global variable that stores the input of the user */
/**
 * main - mock shell
 * @ac: number of arguments
 * @argv: pointer to pointer to cha
 *
 * Return: 0 if succeeds, 1 if fails
 */
int main(__attribute__((unused))int ac, __attribute__((unused))char **argv)
{
	size_t buff;
	ssize_t characters;
	pid_t pid;
	char **av, *env[] = {NULL}, *user_input = NULL;

	while (true)
	{
		buff = 0;
		prompt();
		characters = getline(&user_input, &buff, stdin);
		if (characters == -1)
		{
			if (characters == EOF)
				break;
			if (isatty(STDIN_FILENO))
				perror("./shell");
			continue;
		}
		user_input[characters - 1] = '\0';
		if (user_input[0] == ' ')
			remove_space(&user_input);
		if (_strcmp(user_input, "\n") == 0)
		{
			free(user_input);
			user_input = NULL;
			continue;
		}
		if (tokenize(&av, &user_input) == -1)
			continue;
		if (exe_builtins(av, &user_input) == 0)
			continue;
		if (check_existance(av, &user_input) == -1)
			continue;
		pid = fork();
		fork_error(av, &user_input, pid);
		if (pid == 0)
		{
			execute_commands(av, env, &user_input);
			exit(EXIT_SUCCESS);
		}
		else
			wait(NULL);
		free_ptr(av);
		free(user_input);
		user_input = NULL;
	}
	return (0);
}
