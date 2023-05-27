#include "shell.h"
/**
 * _isalpha - alphabet checker
 * @c: character checked
 * Return: 1 if c is alphabet, otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_delimeter - check character if delimeter
 * @c: char checked
 * @delim: string which is delimeter
 * Return: 1 if true, 0 otherwise
 */
int is_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * interact - true if shell in interact mode
 * @info: address for the struct
 *
 * Return: 1 if interact or 0 non-interact
 */
int interact(information_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _atoi - string to integer converter
 * @s: string that needs to be converted
 * Return: 0 if NULL string else the converted number
 */

int _atoi(char *s)
{
	int i, sgn = 1, flg = 0, outpt;
	unsigned int rslt = 0;

	for (i = 0; s[i] != '\0' && flg != 2; i++)
	{
		if (s[i] == '-')
			sgn *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flg = 1;
			rslt *= 10;
			rslt += (s[i] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sgn == -1)
		outpt = -rslt;
	else
		outpt = rslt;

	return (outpt);
}
