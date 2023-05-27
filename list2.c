#include "shell.h"
/**
 * _node_ad - node added at start of list
 * @hd: pointer to hd node
 * @strng: string field
 * @nm: index used by hist
 *
 * Return: size of list
 */
listing_t *_node_ad(listing_t **hd, const char *strng, int nm)
{
	listing_t *nw_hd;

	if (!hd)
		return (NULL);
	nw_hd = malloc(sizeof(listing_t));
	if (!nw_hd)
		return (NULL);
	_memset((void *)nw_hd, 0, sizeof(listing_t));
	nw_hd->nm = nm;
	if (strng)
	{
		nw_hd->strng = _strdupli(strng);
		if (!nw_hd->strng)
		{
			free(nw_hd);
			return (NULL);
		}
	}
	nw_hd->next = *hd;
	*hd = nw_hd;
	return (nw_hd);
}

/**
 * _nod_end_ad - node added to the end
 * @hd: head pointer
 * @strng: string of node
 * @nm: node used by hist
 *
 * Return: size of list
 */
listing_t *_nod_end_ad(listing_t **hd, const char *strng, int nm)
{
	listing_t *nw_node, *node;

	if (!hd)
		return (NULL);

	node = *hd;
	nw_node = malloc(sizeof(listing_t));
	if (!nw_node)
		return (NULL);
	_memset((void *)nw_node, 0, sizeof(listing_t));
	nw_node->nm = nm;
	if (strng)
	{
		nw_node->strng = _strdupli(strng);
		if (!nw_node->strng)
		{
			free(nw_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = nw_node;
	}
	else
		*hd = nw_node;
	return (nw_node);
}

/**
 * del_nod_indx - delete node at an index
 * @hd: pointer to first node
 * @indx: to be deleted
 *
 * Return: 1 on success 0 on fail
 */
int del_nod_indx(listing_t **hd, unsigned int indx)
{
	listing_t *node, *prv_node;
	unsigned int i = 0;

	if (!hd || !*hd)
		return (0);

	if (!indx)
	{
		node = *hd;
		*hd = (*hd)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *hd;
	while (node)
	{
		if (i == indx)
		{
			prv_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prv_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * prnt_lst_string - string element of a listing_t l-list
 * @k: first node
 *
 * Return: list size
 */
size_t prnt_lst_string(const listing_t *k)
{
	size_t i = 0;

	while (k)
	{
		_puts(k->str ? k->str : "(nil)");
		_puts("\n");
		k = k->next;
		i++;
	}
	return (i);
}

/**
 * free_lst - frees nodes
 * @hd_ptr: pointer to head node
 *
 * Return: void
 */
void free_lst(listing_t **hd_ptr)
{
	listing_t *node, *nxt_node, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	node = hd;
	while (node)
	{
		nxt_node = node->next;
		free(node->str);
		free(node);
		node = nxt_node;
	}
	*hd_ptr = NULL;
}
