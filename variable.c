#include "shell.h"
/**
 * chn_chks - continue chaining based on last stats checks
 * @info: sructure parameter
 * @bfa: char buffa
 * @p: pointer to crrnt pos in bufa
 * @i: starting pos in bufa
 * @length: bufa length
 *
 * Return: Void
 */
void chn_chks(information_t *info, char *bfa, size_t *p,
		size_t i, size_t length)
{
	size_t j = *p;

	if (info->cmd_buf_type == AND_COMMAND)
	{
		if (info->status)
		{
			bfa[i] = 0;
			j = length;
		}
	}
	if (info->cmd_buf_type == OR_CMD)
	{
		if (!info->status)
		{
			bfa[i] = 0;
			j = length;
		}
	}

	*p = j;
}

/**
 * rplc_alias - used to replace aliase string that is tokenized
 * @info: structure parameter
 *
 * Return: 1 on success, 0 otherwise
 */
int rplc_alias(information_t *info)
{
	int i;
	listing_t *node;
	char *k;

	for (i = 0; i < 10; i++)
	{
		node = nod_start_wth(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		k = _strchr(node->str, '=');
		if (!k)
			return (0);
		k = _strdupli(k + 1);
		if (!k)
			return (0);
		info->argv[0] = k;
	}
	return (1);
}

/**
 * chains - used to test if current character in bufa is chain delimeter
 * @info: structure parameter
 * @bfa: character bufa
 * @p: pointer to current position in bufa
 *
 * Return: 1 if true, 0 false
 */
int chains(information_t *info, char *bfa, size_t *p)
{
	size_t j = *p;

	if (bfa[j] == '|' && bfa[j + 1] == '|')
	{
		bfa[j] = 0;
		j++;
		info->cmd_buf_type = OR_CMD;
	}
	else if (bfa[j] == '&' && bfa[j + 1] == '&')
	{
		bfa[j] = 0;
		j++;
		info->cmd_buf_type = AND_COMMAND;
	}
	else if (bfa[j] == ';')
	{
		bfa[j] = 0;
		info->cmd_buf_type = CHAIN_COMMAND;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * rplc_str - used to replace a string
 * @old: pointer to the old string
 * @new: new string
 *
 * Return: 1 on success, 0 otherwise
 */
int rplc_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * rplc_var - used to replace variables in tokenized string
 * @info: structure parameter
 *
 * Return: 1 on success, 0 failure
 */
int rplc_var(information_t *info)
{
	int i = 0;
	listing_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			rplc_str(&(info->argv[i]),
					_strdupli(convert_nmb(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			rplc_str(&(info->argv[i]),
					_strdupli(convert_nmb(getpid(), 10, 0)));
			continue;
		}
		node = nod_start_wth(info->env, &info->argv[i][1], '=');
		if (node)
		{
			rplc_str(&(info->argv[i]),
					_strdupli(_strchr(node->str, '=') + 1));
			continue;
		}
		rplc_str(&info->argv[i], _strdupli(""));

	}
	return (0);
}
