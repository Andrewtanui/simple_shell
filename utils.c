#include "shell.h"

/**
 * read_line - Read line input from  user
 *
 * Return: Line input as a string
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(line);
			line = NULL;
		}
		else
		{
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 * split_line - Split  line into args
 * @line: Line to be split into args
 *
 * Return: Array of pointers to the args
 */
char **split_line(char *line)
{
	int bufsize = TOKEN_BUFSIZE;
	int position = 0;
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
		tokens[position] = token;
		position++;

		if (position >= bufsize)
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
	tokens[position] = NULL;

	return (tokens);
}

/**
 * exe_command - Exe command with the given args
 * @args: Arguments passed as parameter
 *
 * Return: Returns 1 to continue with shell exe
 */
int exe_command(char **args)
{
	pid_t pid;
	int stats;

	if (args[0] == NULL)
		return (1);

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execute_command");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("execute_command");
		exit(EXIT_FAILURE);
	}
	else
	{
		do {
			waitpid(pid, &stats, WUNTRACED);
		} while (!WIFEXITED(stats) && !WIFSIGNALED(stats));
	}

	return (1);
}
