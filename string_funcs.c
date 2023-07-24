#include "shell.h"

/*
 * _strlen - counts elements of a string
 * @string: string to count elements of
 *
 * RETURN: number of elements
 */

size_t _strlen(const char *string)
{
	size_t i;

	if (string == NULL)
		return (0);
	for (i = 0; string[i] != '\0'; i++)
		;
	return (i);
}

/*
 * _strcpy - copies src into dest
 * @dest: destination string
 * @src: string to be copied
 *
 * RETURN: pointer to the destination string
 */

char *_strcpy(char *dest, const char *src)
{
	int i;

	if (dest == NULL || src == NULL)
		return (NULL);
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/*
 * _strdup - makes a duplicate of a string
 * @string: string to duplicate
 *
 * RETURN: pointer to the duplicated string
 */

char *_strdup(const char *string)
{
	char *duplicate;

	if (string == NULL)
		return (NULL);
	duplicate = malloc(_strlen(string) + 1);
	if (duplicate == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	_strcpy(duplicate, string);
	return (duplicate);
}

/*
 * _strcat - concatenates dest and src in dest
 * @dest: destination string
 * @src: string to be concatenated with dest
 *
 * RETURN: pointer to the destination string
 */

char *_strcat(char *dest, const char *src)
{
	int i;
	size_t dest_len;

	if (dest == NULL || src == NULL)
		return (NULL);

	dest_len = _strlen(dest);
	for (i = 0; src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}

/*
 * _strncmp - compares s1 and s2 up to n bytes
 * @s1: string to be compared
 * @s2: string to compare s1 to
 * @n: number of bytes to be compared
 *
 * RETURN: int
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	for (i = 0; i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; i++)
		;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}
