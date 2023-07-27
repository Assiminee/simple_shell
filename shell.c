#include "shell.h"

/**
 * main - executes user commands from terminal
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
			{
				free(user_input);
				break;
			}
			if (isatty(STDIN_FILENO))
				perror("./shell");
			continue;
		}
		user_input[characters - 1] = '\0';
		if (pre_execution(&av, &user_input) == -1)
			continue;
		pid = fork();
		fork_error(av, &user_input, pid);
		if (pid == 0)
		{
			execute_commands(av, env);
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

/**
 * pre_execution - steps before executing a command
 * &av: tokenized user input
 * &user_input: input of the user
 *
 * Return: 0 or -1
 */

int pre_execution(char ***av, char **user_input)
{
	if (av == NULL || user_input == NULL)
		return (-1);

	if (check_for_space(user_input) == -1)
		return (-1);

	if (tokenize(av, user_input) == -1)
		return (-1);

	if (exe_builtins(*av, user_input) == 0)
		return (-1);

	if (check_existance(*av, user_input) == -1)
		return (-1);

	return (0);
}

/**
 * check_for_space - checks for leading spaces in user input
 * &user_input: input from the user
 *
 * Return: 0 or -1
 */

int check_for_space(char **user_input)
{
	if ((*user_input)[0] == ' ')
		remove_space(user_input);
	if (_strcmp(*user_input, "\n") == 0)
	{
		free(*user_input);
		user_input = NULL;
		return (-1);
	}
	return (0);
}
