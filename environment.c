#include "shell.h"

/**
 * get_environ_variable - Gets value of an environment variable
 * @vari_name: Name of environment variable
 *
 * Return: Value of the environment variable or NULL if not found
 */
char *get_environ_variable(const char *vari_name)
{
	extern char **environ;
	int i = 0;
	size_t var_len = strlen(vari_name);

	if (environ == NULL)
	{
		return NULL;
	}

	while (environ[i])
	{
		if (strncmp(environ[i], vari_name, var_len) == 0 && environ[i][var_len] == '=')
			return (environ[i] + var_len + 1);
		i++;
	}

	return (NULL);
}

/**
 * set_environ_variable - Set environment variable value
 * @vari_name: Environment variable name
 * @value: Value to be set
 *
 * Return: 0 if success or -1 if failure
 */
int set_environ_variable(const char *vari_name, const char *value)
{
	char *var;
	size_t var_len;

	var_len = strlen(vari_name) + 1 + strlen(value) + 1;
	var = malloc(var_len);
	if (!var)
	{
		perror("set_environ_variable");
		return (-1);
	}

	snprintf(var, var_len, "%s=%s", vari_name, value);
	if (putenv(var) != 0)
	{
		perror("set_environ_variable");
		free(var);
		return (-1);
	}

	return (0);
}
