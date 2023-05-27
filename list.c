#include "shell.h"
/**
 * lst_length - figures out the len of l-list
 * @k: first node pointer
 *
 * Return: list size
 */
size_t lst_length(const listing_t *k)
{
	size_t i = 0;

	while (k)
	{
		k = k->next;
		i++;
	}
	return (i);
}

/**
 * prnt_lst - elements of a listing_t l-list printed
 * @k: first node
 *
 * Return: list size
 */
size_t prnt_lst(const listing_t *k)
{
	size_t i = 0;

	while (k)
	{
		_puts(convert_nmb(k->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(k->str ? k->str : "(nil)");
		_puts("\n");
		k = k->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - gets array of strings
 * @hd: first node point
 *
 * Return: array of strings
 */
char **list_to_strings(listing_t *hd)
{
	listing_t *node = hd;
	size_t i = lst_length(hd), j;
	char **strins;
	char *stre;

	if (!hd || !i)
		return (NULL);
	strins = malloc(sizeof(char *) * (i + 1));
	if (!strins)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		stre = malloc(_strlen(node->stre) + 1);
		if (!stre)
		{
			for (j = 0; j < i; j++)
				free(strins[j]);
			free(strins);
			return (NULL);
		}

		stre = _strcpy(stre, node->stre);
		strins[i] = stre;
	}
	strins[i] = NULL;
	return (strins);
}

/**
 * gt_nod_indx - get index belonging a node
 * @hd: list head
 * @node: node pointer
 *
 * Return: index of node or -1
 */
ssize_t gt_nod_indx(listing_t *hd, listing_t *node)
{
	size_t i = 0;

	while (hd)
	{
		if (hd == node)
			return (i);
		hd = hd->next;
		i++;
	}
	return (-1);
}

/**
 * nod_start_wth - node with string that starts with pref
 * @node: list head
 * @pref: match needed
 * @j: character after pref
 *
 * Return: matched node or null
 */
listing_t *nod_start_wth(listing_t *node, char *pref, char j)
{
	char *m = NULL;

	while (node)
	{
		m = start_with(node->str, pref);
		if (m && ((j == -1) || (*m == j)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
