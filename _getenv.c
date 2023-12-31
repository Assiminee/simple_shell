#include "shell.h"

/**
 * return_value - extracts the value of an environment variable
 * @entry: line containing the key value pair of an env var
 *
 * Return: the value of an env var
 */

char *return_value(const char *entry)
{
	char *value, *ptr, *portion;

	if (entry == NULL)
		return (NULL);
	ptr = _strdup(entry);
	if (ptr == NULL)
	{
		perror("_strdup");
		return (NULL);
	}
	portion = _strtok(ptr, "=");
	portion = _strtok(NULL, "=");
	value = malloc(_strlen(portion) + 1);
	if (value == NULL)
	{
		perror("malloc");
		free(ptr);
		return (NULL);
	}
	value[0] = '\0';
	_strcpy(value, portion);
	free(ptr);
	return (value);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: the name of an environment variable
 *
 * Return: the value of an environment variable
 */

char *_getenv(const char *name)
{
	int i;
	char *value;

	if (name == NULL || env_vars == NULL)
		return (NULL);
	i = 0;
	while (env_vars[i] != NULL)
	{
		if (_strncmp(name, env_vars[i], strlen(name)) == 0)
			break;
		i++;
	}
	value = return_value(env_vars[i]);
	return (value);
}
