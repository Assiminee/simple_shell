#include "shell.h"

/**
 * exit_bul - exits shell
 * @av: user input array to be freed
 * @user_input: pointer to pointer to char
 *
 * Return: void
 */

void exit_bul(char **av, int status, char *shell_name)
{
	int stat;
	char *error_msg;

	if (av == NULL || user_input == NULL)
		return;
	if (av[1] != NULL)
	{
		stat = exit_status(av[1]);
		if (stat == -1)
		{
			error_msg = malloc(_strlen(shell_name) + _strlen(av[1]) + 29);
			_strcpy(error_msg, shell_name);
			_strcat(error_msg, ": 1: exit: Illegal number: ");
			_strcat(error_msg, av[1]);
			_strcat(error_msg, "\n");
			write(2, error_msg, _strlen(error_msg));
			free(error_msg);
			free_ptr(av);
			free(user_input);
			free_ptr(env_vars);
			exit(2);
		}
		else
		{
			free_ptr(av);
			free(user_input);
			free_ptr(env_vars);
			exit(stat);
		}
	}
	free_ptr(av);
	free(user_input);
	free_ptr(env_vars);
	if (status != 0)
		exit(2);
	exit(EXIT_SUCCESS);
}

/**
 * env_bul - prints environment to the console
  @av: pointer to pointer to char
 * @user_input: pointer to pointer to char
 *
 * Return: void
 */

void env_bul(__attribute__((unused)) char **av,
		__attribute__((unused)) int status,
		__attribute__((unused)) char *shell_name)
{
	int i;

	if (av == NULL || user_input == NULL)
		return;

	for (i = 0; env_vars[i] != NULL; i++)
	{
		if (print_to_console(env_vars[i]) < 0 || print_to_console("\n") < 0)
			exit(EXIT_FAILURE);
	}
	free_ptr(av);
	free(user_input);
	user_input = NULL;
}

void _cd(char *path, char *shell_name)
{
	int status;
	char *buff, *wd, *owd;

	if (path == NULL || _strlen(path) == 0)
	{
		buff = malloc(256);
		_setenv("OLDPWD", getcwd(buff, 256));
		wd = _getenv("HOME");
		chdir(wd);
		_setenv("PWD", wd);
		free(wd);
		free(buff);
		return;
	}
	if (_strcmp(path, "-") == 0)
	{
		owd = _getenv("OLDPWD");
		buff = malloc(256);
		_setenv("OLDPWD", getcwd(buff, 256));
		chdir(owd);
		print_to_console(owd);
		write(STDOUT_FILENO, "\n", 1);
		_setenv("PWD", owd);
		free(owd);
		free(buff);
		return;
	}
	status = chdir(path);
	if (status == -1)
	{
		write(2, shell_name, _strlen(shell_name));
		write(2, ": 1: cd: can't cd to ", 21);
		write(2, path, _strlen(path));
		write(2, "\n", 1);
		return;
	}
	buff = malloc(256);
	_setenv("PWD", getcwd(buff, 256));
	free(buff);
}


/**
 * exe_builtins - executes builtins
 * @av: pointer to pointer to char
 * @user_input: pointer to pointer to char
 *
 * Return: int
 */

int exe_builtins(char **av, int status, char *shell_name)
{
	int k;
	builtins bi[] = {
		{"exit", exit_bul},
		{"env", env_bul},
		{NULL, NULL}
	};

	if (av == NULL || user_input == NULL)
		return (-1);
	for (k = 0; bi[k].func_name; k++)
	{
		if (_strcmp(av[0], bi[k].func_name) == 0)
		{
			bi[k].f(av, status, shell_name);
			return (0);
		}
	}
	if (_strcmp(av[0], "setenv") == 0)
	{
		_setenv(av[1], av[2]);
		free_ptr(av);
		free(user_input);
		return (0);
	}
	if (_strcmp(av[0], "unsetenv") == 0)
	{
		_unsetenv(av);
		return (0);
	}
	if (_strcmp(av[0], "cd") == 0)
	{
		_cd(av[1], shell_name);
		free_ptr(av);
		free(user_input);
		return (0);
	}
	return (-1);
}
