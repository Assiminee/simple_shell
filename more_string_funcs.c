#include "main.h"

/*
 * _strcmp - compares two strings
 * @s1: string to compare
 * @s2: string to compare
 *
 * RETURN: int
 */

int _strcmp(const char *s1, const char *s2)
{
	size_t i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
