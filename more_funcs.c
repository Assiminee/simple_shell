#include "shell.h"

/**
 * prompt - displays the shell symbol on the console
 *
 * Return: void
 */

void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		if (print_to_console("#cisfun$ ") < 0)
			exit(EXIT_FAILURE);
	}
}
/**
 * fork_error - deals with a fork error
 * @av: pointer to pointer to char
 * @pid: pid_t
 * user_input: pointer to pointer to char
 *
 * Return: void
 */

void fork_error(char **av, char **user_input, pid_t pid)
{
	if (av == NULL || user_input == NULL)
		exit(EXIT_FAILURE);
	if (pid == -1)
	{
		perror("fork");
		free_ptr(av);
		free(*user_input);
		*user_input = NULL;
		exit(EXIT_FAILURE);
	}
}
