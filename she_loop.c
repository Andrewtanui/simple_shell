#include "shell.h"

/**
 * hsh - shell loop that is main
 * @info: structure parameter
 * @av: argument from the main
 *
 * Return: 0 if success or error code if failure
 */
int hsh(information_t *info, char **av)
{
	ssize_t r = 0;
	int biltn_re = 0;

	while (r != -1 && biltn_re != -2)
	{
		clear_information(info);
		if (interact(info))
			_puts("$ ");
		_errputchar(BUFA_FLUSHA);
		r = get_inpt(info);
		if (r != -1)
		{
			set_information(info, av);
			biltn_re = find_bultn(info);
			if (biltn_re == -1)
				find_command(info);
		}
		else if (interact(info))
			_putchar('\n');
		free_information(info, 0);
	}
	write_histo(info);
	free_information(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (biltn_re == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (biltn_re);
}

/**
 * find_command - used in finding path cmd
 * @info: structure parameter
 *
 * Return: void
 */
void find_command(information_t *info)
{
	char *pth = NULL;
	int i, j;

	info->pth = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delimeter(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	pth = fnd_path(info, _get_env(info, "PATH="), info->argv[0]);
	if (pth)
	{
		info->pth = pth;
		fork_command(info);
	}
	else
	{
		if ((interact(info) || _get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * find_bultn - used to find builtin cmd
 * @info: structure parameter
 *
 * Return: -1 if bultn not found,
 *	0 if bultn found successfully,
 *	1 if bultn found but not successful,
 *	2 if bultn signals exit
 */
int find_bultn(information_t *info)
{
	int i, biltn_re = -1;
	bultin_t builtintbl[] = {
		{"exit", _shell_exit},
		{"env", _me_env},
		{"help", _me_help},
		{"history", _myhisto},
		{"setenv", _me_setenv},
		{"unsetenv", _me_unsetenv},
		{"cd", _me_cd},
		{"alias", _me_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			biltn_re = builtintbl[i].func(info);
			break;
		}
	return (biltn_re);
}

/**
 * fork_command - forks executable and runs command
 * @info: structure parameter
 *
 * Return: void
 */
void fork_command(information_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_information(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}
