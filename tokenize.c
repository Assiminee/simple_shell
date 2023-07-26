#include "shell.h"

/*
 * free_ptr - frees a pointer to pointer to char
 * @args: pointer to pointer to char to be freed
 *
 * RETURN: void
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

/*
 * num_elements - counts words in string
 * @line: char pointer
 *
 * RETURN: number of words
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
	portion = strtok(line_cpy, " \t\n");
	while (portion != NULL)
	{
		count++;
		portion = strtok(NULL, " \t\n");
	}
	free(line_cpy);
	return (count);
}

/*
 * tokenize - splits elements of a string into pointer to pointer to char
 * @line: string to be split
 *
 * RETURN: pointer to pointer to char
 */

char **tokenize(char *line)
{
	char **args;
	char *line_cpy;
	char *portion;
	int i = 0;

	if (line == NULL)
		return (NULL);
	line_cpy = _strdup(line);
	if (line_cpy == NULL)
	{
		perror("strdup");
		return (NULL);
	}
	args = malloc((num_elements(line_cpy) + 1) * sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		free(line_cpy);
		return (NULL);
	}
	portion = strtok(line_cpy, " \t\n");
	while (portion != NULL)
	{
		args[i] = malloc(_strlen(portion) + 1);
		if (args[i] == NULL)
		{
			perror("malloc");
			free(line_cpy);
			free_ptr(args);
			return (NULL);
		}
		args[i][0] = '\0';
		_strcpy(args[i], portion);
		portion = strtok(NULL, " \t\n");
		i++;
	}
	args[i] = NULL;
	free(line_cpy);
	return (args);
}

/*
 * error_message - prints error message to console
 * @command: command called by the user
 * @message: message to be printed
 *
 * RETURN: void
 */

void error_message(char *command, char *message)
{
	char *error_message = NULL;

	if (message == NULL ||
	_strlen(message) == 0 ||
	command == NULL ||
	_strlen(command) == 0)
		exit(EXIT_FAILURE);
	error_message = malloc(_strlen(command) + _strlen(message) + 3);
	if (error_message == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	_strcpy(error_message, command);
	_strcat(error_message, ": ");
	_strcat(error_message, message);
	if (print_to_console(error_message) < 0)
	{
		free(error_message);
		exit(EXIT_FAILURE);
	}
	free(error_message);
}
