#include "shell.h"
/**
 * _puttsfd - shows input string
 * @str: string that need to be shown
 * @fd: filedescriptor written on
 *
 * Return: number of characters put
 */
int _puttsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _puttfd(*str++, fd);
	}
	return (i);
}

/**
 * _errputchar - places char c in stderr
 * @c: char to display
 *
 * Return: 1 on success, -1 on failure
 */
int _errputchar(char c)
{
	static int i;
	static char buf[BUF_SIZE_WRITE];

	if (c == BUFA_FLUSHA || i >= BUF_SIZE_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFA_FLUSHA)
		buf[i++] = c;
	return (1);
}

/**
 * _puttfd - places character c to filedes given
 * @c: character that needs to be printed
 * @fd: filedescriptor written to
 *
 * Return: On success 1 on failure -1
 */
int _puttfd(char c, int fd)
{
	static int i;
	static char buf[BUF_SIZE_WRITE];

	if (c == BUFA_FLUSHA || i >= BUF_SIZE_WRITE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFA_FLUSHA)
		buf[i++] = c;
	return (1);
}

/**
 * _errputs - displays input string
 * @str: string that need to be displayed
 *
 * Return: void
 */
void _errputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_errputchar(str[i]);
		i++;
	}
}
