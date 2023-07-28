#include "shell.h"

/**
 * pre_execution - steps before executing a command
 * &av: tokenized user input
 * &user_input: input of the user
 *
 * Return: 0 or -1
 */

int pre_execution(char ***av, int *status, char *shell_name)
{
	if (av == NULL || user_input == NULL)
		return (-1);

	if (check_for_space() == -1)
		return (-1);

	if (tokenize(av) == -1)
		return (-1);

	if (exe_builtins(*av, *status, shell_name) == 0)
		return (-1);

	if (check_existance(*av, shell_name, status) == -1)
		return (-1);

	return (0);
}

/**
 * check_for_space - checks for leading spaces in user input
 * &user_input: input from the user
 *
 * Return: 0 or -1
 */

int check_for_space(void)
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
	free_ptr(env_vars);
	free(user_input);
	exit(signal);
}

/**
 * valid_exit_arg - checks if exit argument is valid
 * @arg: string holding exit status
 *
 * Return: 0 if valid, -1 if not
 */

int valid_exit_arg(char *arg)
{
	int i;

	if (arg == NULL)
		return (-1);

	for (i = 0; arg[i] != '\0'; i++)
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (-1);
	}
	return (0);
}

int exit_status(char *arg)
{
	if (arg == NULL)
		return (-1);

	if (valid_exit_arg(arg) == 0)
		return (_atoi(arg));
	return (-1);
}
