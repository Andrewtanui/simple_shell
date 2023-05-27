#include "shell.h"
/**
 * _strcmp - does comparison between two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: -1 if s1 < s2, 1 if s1 > s2, 0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strcat - concats two strings
 * @dest: string to be concated to
 * @src: string to be concated from
 *
 * Return: pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	char *pret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (pret);
}

/**
 * start_with - used to chck if string1 starts with string2
 * @string_one: string that needs to be search
 * @string_two: substring being looked for
 *
 * Return: pointer to next char of string_one or NULL
 */
char *start_with(const char *string_one, const char *string_two)
{
	while (*string_two)
		if (*string_two++ != *string_one++)
			return (NULL);
	return ((char *)string_one);
}

/**
 * _strlen - gives length of a string
 * @s: string whose length is to be returned
 *
 * Return: the string length
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
