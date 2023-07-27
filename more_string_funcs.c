#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: string to compare
 * @s2: string to compare
 *
 * Return: int
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

/**
 * _strtok - tokenizes a string using a delimiter
 * @str: pointer to char
 * @delim: const pointer to char
 *
 * Return: pointer to char
 */

char *_strtok(char *str, const char *delim)
{
	static char *token;
	char *newstr;
	int delimCheck;

	delimCheck = 1;
	if (str == NULL)
		str = token;
	while (*str)
	{
		if (_strchr((char *)delim, *str) == NULL)
		{
			if (delimCheck)
			{
				delimCheck = 0;
				newstr = str;
			}
		}
		else
		{
			if (!delimCheck)
			{
				*str = '\0';
				token = str + 1;
				return (newstr);
			}
		}
		str++;
	}
	if (!delimCheck)
	{
		token = str;
		return (newstr);
	}
	return (NULL);
}

/**
 * _strchr - search the first occurence of a char
 * @s: pointer to char
 * @c: pointer to char
 *
 * Return: pointer to char
 */

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/**
 * _atoi - converts a string to an integer.
 * @s: pointer to char
 *
 * Return: int
 */

int _atoi(char *s)
{
	unsigned int num = 0;
	int sign = 1;
	int i = 0;

	if (s == NULL)
		return (-1);

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		if ((s[i] >= '0') && (s[i] <= '9'))
		{
			num *= 10;
			num += (s[i] - '0');
		}
		else
		{
			if (num)
				break;
		}
		i++;
	}
	num *= sign;
	return (num);
}

