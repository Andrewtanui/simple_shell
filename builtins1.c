#include "shell.h"
/**
 * unset_alis - puts alias to string
 * @info: struct of parameters
 * @str: alias of string
 *
 * Return: Always 0 on success and 1 on failure
 */
int unset_alis(information_t *info, char *str)
{
	char *d, c;
	int reta;

	d = _strchr(str, '=');
	if (!d)
		return (1);
	c = *d;
	*d = 0;
	reta = del_nod_indx(&(info->alias),
		gt_nod_indx(info->alias, nod_start_wth(info->alias, str, -1)));
	*d = c;
	return (reta);
}

/**
 * _myhisto - shows history list and line numbers
 * @info: Structure having args that will be used
 *
 *  Return: Always 0
 */
int _myhisto(information_t *info)
{
	prnt_lst(info->history);
	return (0);
}

/**
 * print_alis - displays string of aliases
 * @node: node of alias
 *
 * Return: Always 0 on success or1 on failure
 */
int print_alis(listing_t *node)
{
	char *d = NULL, *b = NULL;

	if (node)
	{
		d = _strchr(node->str, '=');
		for (b = node->str; b <= d; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(d + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * set_alis - puts alias to a string
 * @info: struct having parameters
 * @str: alias to the string
 *
 * Return: Always 0 on success or 1 on failure
 */
int set_alis(information_t *info, char *str)
{
	char *d;

	d = _strchr(str, '=');
	if (!d)
		return (1);
	if (!*++d)
		return (unset_alis(info, str));

	unset_alis(info, str);
	return (_nod_end_ad(&(info->alias), str, 0) == NULL);
}

/**
 * _me_alias - Same as the real alias
 * @info: Structure having arguments that will be used
 *
 *  Return: Always 0
 */
int _me_alias(information_t *info)
{
	int i = 0;
	char *d = NULL;
	listing_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alis(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		d = _strchr(info->argv[i], '=');
		if (d)
			set_alis(info, info->argv[i]);
		else
			print_alis(nod_start_wth(info->alias, info->argv[i], '='));
	}

	return (0);
}
