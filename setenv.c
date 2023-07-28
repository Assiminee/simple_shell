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

int _setenv(char *name, char *value)
{
	int i;
	char *new_entry;

	if (name == NULL || value == NULL
	|| _strlen(name) == 0 || _strlen(value) == 0)
		return (-1);
	new_entry = create_entry(name, value);
	if (new_entry == NULL)
		return (-1);
	for (i = 0; env_vars[i] != NULL; i++)
	{
		if (_strncmp(name, env_vars[i], _strlen(name)) == 0)
		{
			free(env_vars[i]);
			env_vars[i] = malloc(_strlen(new_entry) + 1);
			_strcpy(env_vars[i], new_entry);
			free(new_entry);
			return (0);
		}
	}
	env_vars[i] = malloc(_strlen(new_entry) + 1);
	if (env_vars[i] == NULL)
	{
		perror("malloc");
		free(new_entry);
		return (-1);
	}
	_strcpy(env_vars[i], new_entry);
	env_vars[i + 1] = NULL;
	free(new_entry);
	return (0);
}

int _unsetenv(char **av)
{
	int i;
	bool found = false;

	if (av == NULL || av[1] == NULL || _strlen(av[1]) == 0)
	{
		free_ptr(av);
		free(user_input);
		return (-1);
	}
	for (i = 0; env_vars[i] != NULL; i++)
	{
		if (_strncmp(av[1], env_vars[i], _strlen(av[1])) == 0)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		free(env_vars[i]);
		for (; i < elements(env_vars) - 1; i++)
		{
			env_vars[i] = malloc(_strlen(env_vars[i + 1]) + 1);
			if (env_vars[i] == NULL)
			{
				free_ptr(env_vars);
				env_vars = NULL;
				env_cpy();
				free_ptr(av);
				free(user_input);
				return (-1);
			}
			_strcpy(env_vars[i], env_vars[i + 1]);
			free(env_vars[i + 1]);
		}
		env_vars[i] = NULL;
	}
	free_ptr(av);
	free(user_input);
	return (0);
}
