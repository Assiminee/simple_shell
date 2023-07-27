#include "shell.h"

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
