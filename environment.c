#include "shell.h"
/**
 * _me_setenv - start new env var or modify
 * @info: Structure having used args
 *
 * Return: Always 0
 */
int _me_setenv(information_t *info)
{
	if (info->argc != 3)
	{
		_errputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _me_env - displays the current working environment
 * @info: Structure arguments used
 *
 * Return: Always 0
 */
int _me_env(information_t *info)
{
	prnt_lst_string(info->env);
	return (0);
}

/**
 * _get_env - value of env variable
 * @info: structure arguments used
 * @name: name of environment varariable
 *
 * Return: the value of env var
 */
char *_get_env(information_t *info, const char *name)
{
	listing_t *node = info->env;
	char *d;

	while (node)
	{
		d = start_with(node->str, name);
		if (d && *d)
			return (d);
		node = node->next;
	}
	return (NULL);
}

/**
 * _me_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _me_unsetenv(information_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_errputs("Few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unset_env(info, info->argv[i]);

	return (0);
}

/**
 * pop_env_list - populates linked list of the environment
 * @info: Structure having arguments used
 *
 * Return: Always 0
 */
int pop_env_list(information_t *info)
{
	listing_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_nod_end_ad(&node, environ[i], 0);
	info->env = node;
	return (0);
}
