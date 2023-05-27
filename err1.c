#include "shell.h"
/**
 * remove_cmmnt - removes comments
 * @buf: address to string that needs modification
 *
 * Return: Always 0
 */
void remove_cmmnt(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * _erroratoi - changes string to integer
 * @s: string that need to be converted
 * Return: 0 on success -1 on failure
 */
int _erroratoi(char *s)
{
	int i = 0;
	unsigned long int answer = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			answer *= 10;
			answer += (s[i] - '0');
			if (answer > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (answer);
}

/**
 * print_dec - prints decimal number
 * @input: input to be printed
 * @fd: filedescriptor written on
 *
 * Return: number of characters that have been printed
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, conts = 0;
	unsigned int _absa_, crrnt;

	if (fd == STDERR_FILENO)
		__putchar = _errputchar;
	if (input < 0)
	{
		_absa_ = -input;
		__putchar('-');
		conts++;
	}
	else
		_absa_ = input;
	crrnt = _absa_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_absa_ / i)
		{
			__putchar('0' + crrnt / i);
			conts++;
		}
		crrnt %= i;
	}
	__putchar('0' + crrnt);
	conts++;

	return (conts);
}

/**
 * print_err - prints error message
 * @info: the parameter
 * @estr: string containing error type
 *
 * Return: 0 on success and -1 otherwise
 */
void print_err(information_t *info, char *estr)
{
	_errputs(info->fname);
	_errputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	_errputs(": ");
	_errputs(info->argv[0]);
	_errputs(": ");
	_errputs(estr);
}

/**
 * convert_nmb - same to itoa
 * @num: number used
 * @base: base used
 * @flags: arg flags
 *
 * Return: string
 */
char *convert_nmb(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sgn = 0;
	char *potr;
	unsigned long m = num;

	if (!(flags & UNSIGNED_CONVERSION) && num < 0)
	{
		m = -num;
		sgn = '-';

	}
	array = flags & LOWERCASE_CONVERTER ? "0123456789abcdef" : "0123456789ABCDEF";
	potr = &buffer[49];
	*potr = '\0';

	do	{
		*--potr = array[m % base];
		m /= base;
	} while (m != 0);

	if (sgn)
		*--potr = sgn;
	return (potr);
}
