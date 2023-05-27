#include "shell.h"
/**
 * **strtow2 - used when spliting string into words
 * @string: string to be split
 * @d: delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *string, char d)
{
	int i, j, k, m, nmwrds = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (i = 0; string[i] != '\0'; i++)
		if ((string[i] != d && string[i + 1] == d) ||
				    (string[i] != d && !string[i + 1]) || string[i + 1] == d)
			nmwrds++;
	if (nmwrds == 0)
		return (NULL);
	s = malloc((1 + nmwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nmwrds; j++)
	{
		while (string[i] == d && string[i] != d)
			i++;
		k = 0;
		while (string[i + k] != d && string[i + k] && string[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow - used to split a string into words
 * @string: string input
 * @d: delimeter string
 * Return: pointer to an array of strings, or NULL on failure
 */

char **strtow(char *string, char *d)
{
	int i, j, k, m, nmwrds = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; string[i] != '\0'; i++)
		if (!is_delimeter(string[i], d) &&
				(is_delimeter(string[i + 1], d) || !string[i + 1]))
			nmwrds++;

	if (nmwrds == 0)
		return (NULL);
	s = malloc((1 + nmwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nmwrds; j++)
	{
		while (is_delimeter(string[i], d))
			i++;
		k = 0;
		while (!is_delimeter(string[i + k], d) && string[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
