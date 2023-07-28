#include "shell.h"

/**
 * elements - counts elements of a pointer to pointer to char
 * @tokenized: pointer to pointer to char
 *
 * Return: number of elements
 */

int elements(char **tokenized)
{
	int i;

	if (tokenized == NULL)
		return (0);
	for (i = 0; tokenized[i] != NULL; i++)
		;
	return (i);
}

/**
 * is_path - checks if user input is a path
 * @string: string to check
 *
 * Return: 0 or 1
 */

int is_path(char *string)
{
	int i;

	if (string == NULL)
		return (0);
	for (i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == '/')
		{
			return (1);
		}
	}
	return (0);
}

/**
 * find_path_to_file - finds path to file
 * @fileName: user input
 *
 * Return: full path of file
 */
char *find_path_to_file(char *fileName)
{
	struct stat st;
	char *path_variable;
	char *portion;
	char *fullPath;

	if (fileName == NULL)
		return (NULL);
	if (is_path(fileName))
	{
		if (stat(fileName, &st) == 0)
			return (fileName);
	}
	path_variable = _getenv("PATH");
	portion = _strtok(path_variable, ":");
	while (portion != NULL)
	{
		fullPath = malloc((_strlen(portion) + _strlen(fileName)) + 2);
		if (fullPath == NULL)
		{
			free(path_variable);
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		_strcpy(fullPath, portion);
		_strcat(fullPath, "/");
		_strcat(fullPath, fileName);
		if (stat(fullPath, &st) == 0)
		{
			free(path_variable);
			return (fullPath);
		}
		free(fullPath);
		portion = _strtok(NULL, ":");
	}
	free(path_variable);
	return (NULL);
}
