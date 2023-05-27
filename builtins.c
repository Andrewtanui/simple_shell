#include "shell.h"
/**
 * _me_cd - changes the directory
 * @info: Structure having arguments that will be needed in the func
 *
 * Return: Always 0
 */
int _me_cd(information_t *info)
{
	char *s, *directory, buffer[1024];
	int changedir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directory = _get_env(info, "HOME=");
		if (!directory)
			changedir_ret =
				chdir((directory = _get_env(info, "PWD=")) ? directory : "/");
		else
			changedir_ret = chdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_get_env(info, "OLDPWD=")), _putchar('\n');
		changedir_ret =
			chdir((directory = _get_env(info, "OLDPWD=")) ? directory : "/");
	}
	else
		changedir_ret = chdir(info->argv[1]);
	if (changedir_ret == -1)
	{
		print_err(info, "can't cd to ");
		_errputs(info->argv[1]), _errputchar('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", _get_env(info, "PWD="));
		_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _shell_exit - exit simple shell
 * @info: Structure having potential args
 * Return: exit status or
 * 0 if info.argv[0] != exit
 */
int _shell_exit(information_t *info)
{
	int extchck;

	if (info->argv[1])
	{
		extchck = _erroratoi(info->argv[1]);
		if (extchck == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			_errputs(info->argv[1]);
			_errputchar('\n');
			return (1);
		}
		info->err_num = _erroratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _me_help - changes directory to help page
 * @info: Structure having arguments that will be used
 *
 * Return: Always 0
 */
int _me_help(information_t *info)
{
	char **args_array;

	args_array = info->argv;
	_puts("This is the help page.\n");
	if (0)
		_puts(*args_array);
	return (0);
}
