#include "shell.h"
/**
 * set_information - information_t struct initialization
 * @info: address to the structure
 * @av: arg vec
 */
void set_information(information_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdupli(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rplc_alias(info);
		rplc_var(info);
	}
}

/**
 * clear_information - clears information_t struct
 * @info: address to struct
 */
void clear_information(information_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * free_information - information_t structure freed
 * @info: address of structure
 * @all: true when fields are freed
 */
void free_information(information_t *info, int all)
{
	fffre(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_lst(&(info->env));
		if (info->history)
			free_lst(&(info->history));
		if (info->alias)
			free_lst(&(info->alias));
		fffre(info->environ);
			info->environ = NULL;
		befree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFA_FLUSHA);
	}
}
