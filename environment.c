#include "shell.h"
/**
 * get_environ_variable - Gets value of an environment variable
 * @vari_name: Environment variable
 *
 * Return: Value environment variable or NULL if not found
 */

char *get_environ_variable(const char *vari_name)
{
	char **environ;
	int i = 0;
	size_t var_length = strlen(vari_name);

	while (environ[i])
	{
		if (strncmp(environ[i], vari_name, var_length) == 0 && environ[i][var_length] == '=')
			return (environ[i] + var_length + 1);
		i++;
	}

	return (NULL);
}

/**
 * set_environ_variable - Sets environment variable
 * @vari_name: Environment variable
 * @value: Value to be set
 *
 * Return: 0 if success or -1 if fail
 */
int set_environ_variable(const char *vari_name, const char *value)
{
	char *var;
	size_t var_length;
	char *vari_value;

	var_length = strlen(vari_name) + 1 + strlen(value) + 1;
	var = malloc(var_length);
	if (!var)
	{
		perror("set_environ_variable");
		return (-1);
	}

	snprintf(var, var_length, "%s=%s", vari_name, value);
	if (putenv(var) != 0)
	{
		perror("set_environ_variable");
		free(var);
		return (-1);
	}

	return (0);
}
