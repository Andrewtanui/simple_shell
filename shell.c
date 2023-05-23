#include "shell.h"

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("#cisfun$ ");
		line = read_line();
		args = split_line(line);

		if (args[0] != NULL && strcmp(args[0], "cd") == 0)
		{
			status = ex_cd(args);
		}
		else
		{
			status = ex_command(args);
		}

		free(line);
		free(args);
	} while (status);

	return (0);
}

