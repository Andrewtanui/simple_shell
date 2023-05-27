#include "shell.h"
/**
 * _unset_env - unset environ var
 * @info: Structure with args used
 * @var: string variable
 *
 * Return: 1 on success 0 otherwise
 */
int _unset_env(information_t *info, char *var)
{
	listing_t *node = info->env;
	size_t i = 0;
	char *d;

	if (!node || !var)
		return (0);

	while (node)
	{
		d = start_with(node->str, var);
		if (d && *d == '=')
		{
			info->env_changed = del_nod_indx(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * get_environ - display array of string of environvironment
 * @info: structure having arguments used
 *
 * Return: Always 0
 */
char **get_environ(information_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _set_env - starts new env var or modifies
 * @info: Structure having arg used
 * @variable: string variable
 * @value: string value
 * Return: Always 0
 */
int _set_env(information_t *info, char *variable, char *value)
{
	char *buf = NULL;
	listing_t *node;
	char *d;

	if (!variable || !value)
		return (0);

	buf = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, variable);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		d = start_with(node->str, variable);
		if (d && *d == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_nod_end_ad(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
