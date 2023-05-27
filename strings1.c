#include "shell.h"
/**
 * _strdupli - duplicate string
 * @str: string to be duplicated
 *
 * Return: pointer to the duplicated string
 */
char *_strdupli(const char *str)
{
	int len = 0;
	char *pret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	pret = malloc(sizeof(char) * (len + 1));
	if (!pret)
		return (NULL);
	for (len++; len--;)
		pret[len] = *--str;
	return (pret);
}

/**
 * _puts - used to print a string
 * @str: string to be printed
 *
 * Return: void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - used to display char in stdout
 * @c: character to print
 *
 * Return: 1 on success, -1 error
 */
int _putchar(char c)
{
	static int i;
	static char buf[BUF_SIZE_WRITE];

	if (c == BUFA_FLUSHA || i >= BUF_SIZE_WRITE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFA_FLUSHA)
		buf[i++] = c;
	return (1);
}

/**
 * _strcpy - copy string
 * @dest: str copied to
 * @src: str copied from
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
