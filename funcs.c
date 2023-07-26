#include "shell.h"

/**
 * check_existance - checks if command exists
 * @av: list of arguments to be passed during execution
 * @buff: size of the buffer lineptr
 *
 * Return: void
 */

int check_existance(char **av, size_t *buff)
{
	char *abs_path;

	abs_path = find_path_to_file(av[0]);
	if (abs_path == NULL)
	{
		error_message(av[0], "command not found\n");
		free_ptr(av);
		*buff = 0;
		return (-1);
	}
	av[0] = abs_path;
	return (0);
}

/**
 * execute_commands - executes user commands
 * @av: list of arguments to be passed during execution
 * @env: environment variables
 * @buff: size of the buffer lineptr
 *
 * Return: void
 */

void execute_commands(char **av, char *env[], size_t *buff)
{
	int exe;

	exe = execve(av[0], av, env);
	if (exe == -1)
		perror("./shell");
	free_ptr(av);
	free(user_input);
	user_input = NULL;
	*buff = 0;
}

/**
 * print_to_console - prints to the console
 * @string: text to print to the console
 *
 * Return: 0 if success, -1 if failure
 */

int print_to_console(char *string)
{
	if (string == NULL)
		return (-1);

	if (write(STDOUT_FILENO, string, _strlen(string)) < 0)
	{
		perror("write");
		return (-1);
	}
	return (0);
}

/**
 * remove_space - removes leading spaces
 *
 * Return: void
 */

void remove_space(void)
{
	if (user_input == NULL)
		return;

	while (*user_input == ' ')
		user_input++;
}
