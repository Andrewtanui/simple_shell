#include "shell.h"

/**
 * befree - free pointers then NULL addresses
 * @potr: pointer to free
 *
 * Return: if freed 1 or 0 if not freed
 */
int befree(void **potr)
{
	if (potr && *potr)
	{
		free(*potr);
		*potr = NULL;
		return (1);
	}
	return (0);
}
