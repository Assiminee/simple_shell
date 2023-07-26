#include "shell.h"

/*
 * elements - counts elements of a pointer to pointer to char
 * @tokenized: pointer to pointer to char
 *
 * RETURN: number of elements
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

/*
 * fill_av - fills the array of arguments
 * @tokenized: pointer to pointer to char
 *
 * RETURN: pointer to pointer to char
 */

char **fill_av(char **tokenized)
{
	int i;
	char **av;

	if (tokenized == NULL)
		return (NULL);
	av = malloc((elements(tokenized) + 1) * sizeof(char *));
	if (av == NULL)
	{
		perror("malloc");
		free_ptr(tokenized);
		return (NULL);
	}
	for (i = 0; tokenized[i] != NULL; i++)
	{
		av[i] = malloc(_strlen(tokenized[i]) + 1);
		if (av[i] == NULL)
		{
			perror("malloc");
			free_ptr(av);
			free_ptr(tokenized);
			return (NULL);
		}
		av[i][0] = '\0';
		_strcpy(av[i], tokenized[i]);
	}
	av[i] = NULL;
	free_ptr(tokenized);
	return (av);
}

/*
 * is_path - checks if user input is a path
 * @string: string to check
 *
 * RETURN: 0 or 1
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

/*
 * find_path_to_file - finds path to file
 * @fileName: user input
 *
 * RETURN: full path of file
 */
char *find_path_to_file(char *fileName)
{
	struct stat st;
	char *path_variable;
	char *portion;
	char *fullPath;

	if (fileName == NULL)
		return (NULL);
	path_variable = _getenv("PATH");
	portion = strtok(path_variable, ":");
	while (portion != NULL)
	{
		if (is_path(fileName))
		{
			if (stat(fileName, &st) == 0)
				return (fileName);
		}
		fullPath = malloc((_strlen(portion) + _strlen(fileName)) + 2);
		if (fullPath == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		_strcpy(fullPath, portion);
		_strcat(fullPath, "/");
		_strcat(fullPath, fileName);
		if (stat(fullPath, &st) == 0)
			return (fullPath);
		free(fullPath);
		portion = strtok(NULL, ":");
	}
	return (NULL);
}