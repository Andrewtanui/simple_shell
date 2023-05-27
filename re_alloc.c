#include "shell.h"
/**
 * fffre - used to free string of strings
 * @ss: string of strings
 */
void fffre(char **ss)
{
	char **b = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(b);
}

/**
 * _realloc - used to reallocate memory block
 * @potr: pointer to previously allocated block
 * @od_sze: memory of previous block
 * @nw_sze: memory of new block
 *
 * Return: pointer to old block
 */
void *_realloc(void *potr, unsigned int od_sze, unsigned int nw_sze)
{
	char *d;

	if (!potr)
		return (malloc(nw_sze));
	if (!nw_sze)
		return (free(potr), NULL);
	if (nw_sze == od_sze)
		return (potr);

	d = malloc(nw_sze);
	if (!d)
		return (NULL);

	od_sze = od_sze < nw_sze ? od_sze : nw_sze;
	while (od_sze--)
		d[od_sze] = ((char *)potr)[od_sze];
	free(potr);
	return (d);
}

/**
 * _memset - sets mem with bytes
 * @c: pointer to memory location to be set
 * @m: amount of mem to fill *c with
 * @f: amount of memory that need to be filled
 * Return: pointer to memory area set
 */
char *_memset(char *c, char m, unsigned int f)
{
	unsigned int i;

	for (i = 0; i < f; i++)
		c[i] = m;
	return (c);
}
