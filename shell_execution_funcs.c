#include "shell.h"

/**
 * pre_execution - steps before executing a command
 * &av: tokenized user input
 * &user_input: input of the user
 *
 * Return: 0 or -1
 */

int pre_execution(char ***av, int status)
{
	if (av == NULL || user_input == NULL)
		return (-1);

	if (check_for_space() == -1)
		return (-1);

	if (tokenize(av) == -1)
		return (-1);

	if (exe_builtins(*av, status) == 0)
		return (-1);

	if (check_existance(*av) == -1)
		return (-1);

	return (0);
}

/**
 * check_for_space - checks for leading spaces in user input
 * &user_input: input from the user
 *
 * Return: 0 or -1
 */

int check_for_space()
{
	if (user_input[0] == ' ')
		remove_space();
	if (_strcmp(user_input, "\n") == 0)
	{
		free(user_input);
		user_input = NULL;
		return (-1);
	}
	return (0);
}

/**
 * handleCtrlC - signal handler
 * &signal: signal of the process
 *
 * Return: void
 */

void handleCtrlC(int signal)
{
	free(user_input);
	exit(signal);
}
