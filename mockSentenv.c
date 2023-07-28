#include "shell.h"

bool check_var(const char *name)
{
	int i;

	if (name == NULL)
		return (false);
	i = 0;
		
	if (name[i] >= '0' && name[i] <= '9')
		return (false);
	while (name[i] != '\0')
	{
		if (!((name[i] >= 'A' && name[i] <= 'Z') ||
			(name[i] >= 'a' && name[i] <= 'z') ||
			(name[i] >= '0' && name[i] <= '9') ||
			(name[i] == '_')))
			return (false);
		i++;
	}
	return (true);
}
			
char *create_entry(const char *name, const char *value)
{
	char *new_entry;

	if (name == NULL || value == NULL ||
	_strlen(name) == 0 || _strlen(value) == 0)
		return (NULL);

	new_entry = malloc(_strlen(name) + _strlen(value) + 2);
	if (new_entry == NULL)
	{
		perror("malloc()");
		return (NULL);
	}
	_strcpy(new_entry, name);
	_strcat(new_entry, "=");
	_strcat(new_entry, value);
	return (new_entry);
}

int _setenv(char **av)
{
	int i;
	char *new_entry;

	if (av == NULL || av[1] == NULL ||
	av[2] == NULL || _strlen(av[1]) == 0 ||
	_strlen(av[2]) == 0)
	{
		free_ptr(av);
		free(user_input);
		return (-1);
	}

	new_entry = create_entry(av[1], av[2]);
	if (new_entry == NULL)
	{
		free_ptr(av);
		free(user_input);
		return (-1);
	}
	for (i = 0; env_vars[i] != NULL; i++)
	{
		if (_strncmp(av[1], env_vars[i], _strlen(av[1])) == 0)
		{
			free(env_vars[i]);
			env_vars[i] = malloc(_strlen(new_entry) + 1);
			_strcpy(env_vars[i], new_entry);
			free_ptr(av);
			free(user_input);
			free(new_entry);
			return (0);
		}
	}
	env_vars[i] = malloc(_strlen(new_entry) + 1);
	if (env_vars[i] == NULL)
	{
		perror("malloc");
		free(new_entry);
		free_ptr(av);
		free(user_input);
		return (-1);
	}
	_strcpy(env_vars[i], new_entry);
        env_vars[i + 1] = NULL;
	free(new_entry);
	free_ptr(av);
	free(user_input);
	return (0);
}
