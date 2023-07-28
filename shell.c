#include "shell.h"
char *user_input = NULL;
char **env_vars = NULL;
/**
 * main - executes user commands from terminal
 * @ac: number of arguments
 * @argv: pointer to pointer to cha
 *
 * Return: 0 if succeeds, 1 if fails
 */

int main(__attribute__((unused))int ac, char **argv)
{
	size_t buff;
	ssize_t characters;
	pid_t pid;
	char **av, *shell_name = argv[0];
	int status = 0;

	signal(SIGINT, handleCtrlC);
	if (env_cpy() == -1)
		return (-1);
	while (true)
	{
		_setenv("LC_COLLATE", "en_US.UTF-8");
		buff = 0;
		prompt();
		characters = getline(&user_input, &buff, stdin);
		if (characters == -1)
		{
			if (characters == EOF)
			{
				free_ptr(env_vars);
				free(user_input);
				break;
			}
			if (isatty(STDIN_FILENO))
				perror("./shell");
			continue;
		}
		user_input[characters - 1] = '\0';
		if (pre_execution(&av, &status, shell_name) == -1)
			continue;
		pid = fork();
		fork_error(av, pid);
		if (pid == 0)
		{
			execute_commands(av, env_vars);
			exit(EXIT_SUCCESS);
		}
		else
			wait(&status);
		free_ptr(av);
		free(user_input);
		user_input = NULL;
	}
	return (0);
}
