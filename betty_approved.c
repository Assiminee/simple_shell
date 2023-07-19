#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point
 * @ac: number of arguments passed
 * @av: pointer to arguments passed
 *
 * return: 0
 */

int main(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Usage: %s string ...\n", av[0]);
	}
	else
	{
		int i;

		for (i = 0; i < ac; i++)
		{
			printf("argument %d: %s\n", i + 1, av[i]);
		}
	}
	return (0);
}
