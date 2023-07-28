#include "shell.h"

/**
 * check_existance - checks if command exists
 * @av: list of arguments to be passed during execution
 * @user_input: pointer to pointer to char
 *
 * Return: void
 */

int check_existance(char **av, char *shell_name, int *status)
{
	char *abs_path = find_path_to_file(av[0]);
	DIR *dir;

	if (abs_path == NULL)
	{
		error_message(av[0], shell_name);
		free_ptr(av);
		free(user_input);
		user_input = NULL;
		return (-1);
	}
	if (_strcmp(av[0], abs_path) == 0)
		av[0] = abs_path;
	else
	{
		_strcpy(av[0], abs_path);
		free(abs_path);
	}
	if (av[1] != NULL && _strlen(av[1]) != 0 && is_path(av[1]))
	{
		dir = opendir(av[1]);
		if (dir == NULL)
		{
			write(2, av[0], _strlen(av[0]));
			write(2, ": cannot access '", 17);
			write(2, av[1], _strlen(av[1]));
			write(2, "': No such file or directory\n", 29);
			*status = 2;
			free_ptr(av);
			free(user_input);
			return (-1);
		}
		*status = 0;
		free(dir);
	}
	return (0);
}

/**
 * execute_commands - executes user commands
 * @av: list of arguments to be passed during execution
 * @env: environment variables
 * @user_input: pointer to pointer to char
 *
 * Return: void
 */

void execute_commands(char **av, char *env[])
{
	int exe;

	exe = execve(av[0], av, env);
	if (exe == -1)
		perror("./shell");
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
 * @user_input: pointer to pointer to char
 *
 * Return: void
 */

void remove_space(void)
{
	char *temp;

	if (user_input == NULL)
		return;
	temp = user_input;
	while (*temp == ' ')
		temp++;
	_strcpy(user_input, temp);
}
