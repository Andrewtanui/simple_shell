#include "shell.h"

/**
 * ex_exit - Exit built-in command
 *
 * Return: Always returns 0 to exit shell
 */
int ex_exit(void)
{
	return (0);
}

/**
 * ex_env - Env built-in command
 *
 * Return: Always returns 1 to continue the shell
 */
int ex_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (1);
}

/**
 * ex_cd - Cd built-in command
 * @args: Args passed as parameters
 *
 * Return: 1 to continue with the shell
 */
int ex_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "cd: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}

	return (1);
}

