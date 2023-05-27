#include "shell.h"
/**
 * duplicte_characters - character duplcation
 * @pathstring: string path
 * @strt: index for starting
 * @stp: index for stopping
 *
 * Return: pointer to new buffa
 */
char *duplicte_characters(char *pathstring, int strt, int stp)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (j = 0, i = strt; i < stp; i++)
		if (pathstring[i] != ':')
			buf[j++] = pathstring[i];
	buf[j] = 0;
	return (buf);
}

/**
 * is_command - is file executable or not
 * @infor: structure for information
 * @pth: file path
 *
 * Return: 1 if true 0 if false
 */
int is_command(information_t *infor, char *pth)
{
	struct stat st;

	(void)infor;
	if (!pth || stat(pth, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * fnd_path - finds the PATH string command
 * @info: information struct
 * @pathstring: string with path
 * @command: command looked for
 *
 * Return: command path if found, otherwise NULL
 */
char *fnd_path(information_t *info, char *pathstring, char *command)
{
	int i = 0, curret_postn = 0;
	char *pth;

	if (!pathstring)
		return (NULL);
	if ((_strlen(command) > 2) && start_with(command, "./"))
	{
		if (is_command(info, command))
			return (command);
	}
	while (1)
	{
		if (!pathstring[i] || pathstring[i] == ':')
		{
			pth = duplicte_characters(pathstring, curret_postn, i);
			if (!*pth)
				_strcat(pth, command);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, command);
			}
			if (is_command(info, pth))
				return (pth);
			if (!pathstring[i])
				break;
			curret_postn = i;
		}
		i++;
	}
	return (NULL);
}
