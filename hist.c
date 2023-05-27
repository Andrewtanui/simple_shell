#include "shell.h"
/**
 * write_histo - creates hist file
 * @info: strc paramtr
 *
 * Return: 1 on success -1 on failure
 */
int write_histo(information_t *info)
{
	ssize_t fd;
	char *filnm = get_histo_file(info);
	listing_t *node = NULL;

	if (!filnm)
		return (-1);

	fd = open(filnm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filnm);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_puttsfd(node->str, fd);
		_puttfd('\n', fd);
	}
	_puttfd(BUFA_FLUSHA, fd);
	close(fd);
	return (1);
}

/**
 * get_histo_file - lookss for history file
 * @info: structure paramtr
 *
 * Return: string with hist file
 */

char *get_histo_file(information_t *info)
{
	char *bfa, *direc;

	direc = _get_env(info, "HOME=");
	if (!direc)
		return (NULL);
	bfa = malloc(sizeof(char) * (_strlen(direc) + _strlen(HISTORY_FILE) + 2));
	if (!bfa)
		return (NULL);
	bfa[0] = 0;
	_strcpy(bfa, direc);
	_strcat(bfa, "/");
	_strcat(bfa, HISTORY_FILE);
	return (bfa);
}

/**
 * read_histo - get hist from file
 * @info: struc paramtr
 *
 * Return: histcount success 0 on failure
 */
int read_histo(information_t *info)
{
	int i, lust = 0, lncont = 0;
	ssize_t fd, redleng, filsize = 0;
	struct stat st;
	char *bfa = NULL, *filnm = get_histo_file(info);

	if (!filnm)
		return (0);

	fd = open(filnm, O_RDONLY);
	free(filnm);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		filsize = st.st_size;
	if (filsize < 2)
		return (0);
	bfa = malloc(sizeof(char) * (filsize + 1));
	if (!bfa)
		return (0);
	redleng = read(fd, bfa, filsize);
	bfa[filsize] = 0;
	if (redleng <= 0)
		return (free(bfa), 0);
	close(fd);
	for (i = 0; i < filsize; i++)
		if (bfa[i] == '\n')
		{
			bfa[i] = 0;
			build_histo_lst(info, bfa + lust, lncont++);
			lust = i + 1;
		}
	if (lust != i)
		build_histo_lst(info, bfa + lust, lncont++);
	free(bfa);
	info->histcount = lncont;
	while (info->histcount-- >= HISTORY_MAXIMUM)
		del_nod_indx(&(info->history), 0);
	renmb_histo(info);
	return (info->histcount);
}

/**
 * renmb_histo - renumber hist l-list
 * @info: Structure having expected arguments
 *
 * Return: histcount
 */
int renmb_histo(information_t *info)
{
	listing_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

/**
 * build_histo_lst - addition of entry to a hist l-list
 * @info: structure with expected arguments
 * @bfa: buffa
 * @lncont: history lincont, histcont
 *
 * Return: Always 0
 */
int build_histo_lst(information_t *info, char *bfa, int lncont)
{
	listing_t *node = NULL;

	if (info->history)
		node = info->history;
	_nod_end_ad(&node, bfa, lncont);

	if (!info->history)
		info->history = node;
	return (0);
}
