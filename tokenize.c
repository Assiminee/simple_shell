#include "shell.h"

/**
 * free_ptr - frees a pointer to pointer to char
 * @args: pointer to pointer to char to be freed
 *
 * Return: void
 */

void free_ptr(char **args)
{
	int i;

	if (args == NULL)
		return;
	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	free(args);
}

/**
 * num_elements - counts words in string
 * @line: char pointer
 *
 * Return: number of words
 */

int num_elements(char *line)
{
	char *line_cpy;
	char *portion;
	int count = 0;

	if (line == NULL)
		return (0);
	line_cpy = _strdup(line);
	if (line_cpy == NULL)
	{
		perror("strdup");
		return (0);
	}
	portion = _strtok(line_cpy, " \t\n");
	while (portion != NULL)
	{
		count++;
		portion = _strtok(NULL, " \t\n");
	}
	free(line_cpy);
	return (count);
}

/**
 * tokenize - splits elements of a string into pointer to pointer to char
 * @line: string to be split
 * @args: pointer
 *
 * Return: pointer to pointer to char
 */

int tokenize(char ***args)
{
	char *line_cpy, *portion;
	int i = 0, len = 1024;

	if (user_input == NULL || args == NULL)
		return (-1);
	line_cpy = _strdup(user_input);
	if (line_cpy == NULL)
	{
		perror("strdup");
		free(user_input);
		return (-1);
	}
	*args = malloc((num_elements(line_cpy) + 1) * sizeof(char *));
	if (*args == NULL)
	{
		perror("malloc");
		free(line_cpy);
		free(user_input);
		return (-1);
	}
	portion = _strtok(line_cpy, " \t\n");
	while (portion != NULL)
	{
		(*args)[i] = malloc(len + 1);
		if ((*args)[i] == NULL)
		{
			perror("malloc");
			free_ptr(*args);
			free(line_cpy);
			free(user_input);
			return (-1);
		}
		_strcpy((*args)[i], portion);
		portion = _strtok(NULL, " \t\n");
		i++;
		len = _strlen(portion) + 1;
	}
	(*args)[i] = NULL;
	free(line_cpy);
	return (0);
}

/**
 * error_message - prints error message to console
 * @command: command called by the user
 * @message: message to be printed
 *
 * Return: void
 */

void error_message(char *command, char *shell_name)
{
	char *error_message;

	if (shell_name == NULL ||
	_strlen(shell_name) == 0 ||
	command == NULL ||
	_strlen(command) == 0)
	{
		free_ptr(env_vars);
		exit(EXIT_FAILURE);
	}
	error_message = malloc(_strlen(shell_name) + _strlen(command) + 18);
	if (error_message == NULL)
	{
		perror("malloc");
		free_ptr(env_vars);
		exit(EXIT_FAILURE);
	}
	_strcpy(error_message, shell_name);
	_strcat(error_message, ": 1: ");
	_strcat(error_message, command);
	_strcat(error_message, ": not found\n");
	if (write(2, error_message, _strlen(error_message)) < 0)
	{
		free(error_message);
		free_ptr(env_vars);
		exit(EXIT_FAILURE);
	}
	free(error_message);
}

