#include "shell.h"
char *user_input = NULL;
/**
 * main - executes user commands from terminal
 * @ac: number of arguments
 * @argv: pointer to pointer to cha
 *
 * Return: 0 if succeeds, 1 if fails
 */

int main(__attribute__((unused))int ac, __attribute__((unused))char **argv)
{
	size_t buff;
	ssize_t characters;
	pid_t pid;
	char **av, *env[] = {NULL};

	signal(SIGINT, handleCtrlC);
	while (true)
	{
		buff = 0;
		prompt();
		characters = getline(&user_input, &buff, stdin);
		if (characters == -1)
		{
			if (characters == EOF)
			{
				free(user_input);
				break;
			}
			if (isatty(STDIN_FILENO))
				perror("./shell");
			continue;
		}
		user_input[characters - 1] = '\0';
		if (pre_execution(&av) == -1)
			continue;
		pid = fork();
		fork_error(av, pid);
		if (pid == 0)
		{
			execute_commands(av, env);
			exit(EXIT_SUCCESS);
		}
		else
			wait(NULL);
		free_ptr(av);
		free(user_input);
		user_input = NULL;
	}
	return (0);
}
