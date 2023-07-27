#include "shell.h"

/**
 * exit_bul - exits shell
 * @av: user input array to be freed
 * @user_input: pointer to pointer to char
 *
 * Return: void
 */

void exit_bul(char **av, char **user_input)
{
	if (av == NULL || user_input == NULL)
		return;

	free_ptr(av);
	free(*user_input);
	exit(EXIT_SUCCESS);
}

/**
 * env_bul - ...
 * @av: pointer to pointer to char
 * @user_input: pointer to pointer to char
 *
 * Return: void
 */

void env_bul(__attribute__((unused)) char **av, char **user_input)
{
	int i;

	if (av == NULL || user_input == NULL)
		return;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (print_to_console(environ[i]) < 0 || print_to_console("\n") < 0)
			exit(EXIT_FAILURE);
	}
	free_ptr(av);
	free(*user_input);
	*user_input = NULL;
}

/**
 * exe_vuiltins - ...
 * @av: pointer to pointer to char
 * @user_input: pointer to pointer to char
 *
 * Return: int
 */

int exe_builtins(char **av, char **user_input)
{
	int k;
	builtins bi[] = {
		{"exit", exit_bul},
		{"env", env_bul},
		{NULL, NULL}
	};

	if (av == NULL || user_input == NULL)
		return (-1);
	for (k = 0; bi[k].func_name; k++)
	{
		if (_strcmp(av[0], bi[k].func_name) == 0)
		{
			bi[k].f(av, user_input);
			return (0);
		}
	}
	return (-1);
}
