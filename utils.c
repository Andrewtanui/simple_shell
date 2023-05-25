#include "shell.h"

/**
 * read_line - Read line input
 *
 * Return: Line input
 */
char *read_line(void)
{
	char *lin = NULL;
	size_t bufsize = 0;

	if (getline(&lin, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(lin);
			lin = NULL;
		}
		else
		{
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}

	return (lin);
}

/**
 * split_line - Split line into args
 * @line: Line split
 *
 * Return: Array of pointers to the args
 */
char **split_line(char *line)
{
	int bufsize = TOKEN_BUFSIZE;
	int pos = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("split_line");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIMITERS);
	while (token != NULL)
	{
		tokens[pos] = token;
		pos++;

		if (pos >= bufsize)
		{
			bufsize += TOKEN_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));

			if (!tokens)
			{
				perror("split_line");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	tokens[pos] = NULL;

	return (tokens);
}

/**
 * execute_command - Execute command with given args
 * @args: Arguments passed
 *
 * Return: 1 to continue with shell
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		char *args[] = {"/bin/sh", "-c", args, NULL};

		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		do {
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
}
