#include "shell.h"

/*
 * prompt - displays the shell symbol on the console
 *
 * RETURN: void
 */

void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		if (print_to_console("$ ") < 0)
			exit(EXIT_FAILURE);
	}
}

void fork_error(char **av, pid_t pid)
{
	if (av == NULL)
		exit(EXIT_FAILURE);
	if (pid == -1)
	{
		perror("fork");
		free_ptr(av);
		free(user_input);
		exit(EXIT_FAILURE);
	}
}
