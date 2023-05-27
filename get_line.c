#include "shell.h"
/**
 * inpt_bufa - chain cmmnds for bufas
 * @info: struct paramtr
 * @bfa: address to buffer
 * @length: len variable add
 *
 * Return: the bytes that are read
 */
ssize_t inpt_bufa(information_t *info, char **bfa, size_t *length)
{
	ssize_t m = 0;
	size_t len_pi = 0;

	if (!*length)
	{
		free(*bfa);
		*bfa = NULL;
		signal(SIGINT, sigintHandler);
#if USING_GETLINE
		m = getline(bfa, &len_pi, stdin);
#else
		m = _get_line(info, bfa, &len_pi);
#endif
		if (m > 0)
		{
			if ((*bfa)[m - 1] == '\n')
			{
				(*bfa)[m - 1] = '\0';
				m--;
			}
			info->linecount_flag = 1;
			remove_cmmnt(*bfa);
			build_histo_lst(info, *bfa, info->histcount++);
			{
				*length = m;
				info->cmd_buf = bfa;
			}
		}
	}
	return (m);
}

/**
 * read_bfa - reads the buffa
 * @info: parameter struct
 * @bfa: buffa
 * @i: the size of bufa
 *
 * Return: r
 */
ssize_t read_bfa(information_t *info, char *bfa, size_t *i)
{
	ssize_t h = 0;

	if (*i)
		return (0);
	h = read(info->readfd, bfa, BUFA_SIZE);
	if (h >= 0)
		*i = h;
	return (h);
}

/**
 * get_inpt - gets whole line without /n
 * @info: structure parameter
 *
 * Return: bytes that have been read
 */
ssize_t get_inpt(information_t *info)
{
	static char *bef;
	static size_t i, j, length;
	ssize_t h = 0;
	char **bef_p = &(info->arg), *p;

	_putchar(BUFA_FLUSHA);
	h = inpt_bufa(info, &bef, &length);
	if (h == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = bef + i;

		chn_chks(info, bef, &j, i, length);
		while (j < length)
		{
			if (chains(info, bef, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			info->cmd_buf_type = NORMAL_CMD;
		}

		*bef_p = p;
		return (_strlen(p));
	}

	*bef_p = bef;
	return (h);
}

/**
 * _get_line - fetch next line from STDIN
 * @info: structure paramtr
 * @potr: pointer to buffa
 * @length: size pointer buffer
 *
 * Return: s which is pointer to len
 */
int _get_line(information_t *info, char **potr, size_t *length)
{
	static char buf[BUFA_SIZE];
	static size_t i, ln;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *nw_p = NULL, *c;

	p = *potr;
	if (p && length)
		s = *length;
	if (i == ln)
		i = ln = 0;

	r = read_bfa(info, buf, &ln);
	if (r == -1 || (r == 0 && ln == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : ln;
	nw_p = _realloc(p, s, s ? s + k : k + 1);
	if (!nw_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(nw_p, buf + i, k - i);
	else
		_strncpy(nw_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = nw_p;

	if (length)
		*length = s;
	*potr = p;
	return (s);
}

/**
 * sigintHandler - ctrl-C block
 * @sig_num: sgnl nmb
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFA_FLUSHA);
}
