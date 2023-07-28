#include "shell.h"

int num_env_vars(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
		;
	return (i);
}

int env_cpy(void)
{
	int i;

	env_vars = malloc((num_env_vars() + 41) * sizeof(char *));
	if (env_vars == NULL)
		return (-1);
	for (i = 0; environ[i] != NULL; i++)
	{
		env_vars[i] = malloc(_strlen(environ[i]) + 1);
		if (env_vars[i] == NULL)
			return (-1);
		_strcpy(env_vars[i], environ[i]);
	}
	env_vars[i] = NULL;
	return (0);
}