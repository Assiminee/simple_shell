#include "shell.h"

/*
 * exit_bul - exits shell
 * @av: user input array to be freed
 *
 * RETURN: void
 */

void exit_bul(char **av)
{
	if (av == NULL)
		return;

	free_ptr(av);
	free(user_input);
	exit(EXIT_SUCCESS);
}

void env_bul(__attribute__((unused)) char **av)
{
	int i;

	if (av == NULL)
		return;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (print_to_console(environ[i]) < 0 || print_to_console("\n") < 0)
			exit(EXIT_FAILURE);
	}
}

void exe_builtins(char **av)
{
	int k;
	builtins bi[] = {
		{"exit", exit_bul},
		{"env", env_bul},
		{NULL, NULL}
	};

	if (av == NULL)
		return;
	for (k = 0; bi[k].func_name; k++)
	{
		if (_strcmp(av[0], bi[k].func_name) == 0)
			bi[k].f(av);
	}
}
