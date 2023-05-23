#include "shell.h"
/**
 * read_line - Read line input from the user.
 *
 * Return: Line input as a string.
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
 * @line: Line split into args
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
 * ex_command - Execute command with given args
 * @args: Arguments passed as parameters
 *
 * Return: 1 to continue with shell
 */

int ex_command(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
	{
		return (1);
	}

	char *command = args[0];
	char *path = get_environ_variable("PATH");
	char *path_token = strtok(path, ":");
	struct stat st;

	while (path_token != NULL)
	{
		char *full_path = malloc(strlen(path_token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("ex_command");
			exit(EXIT_FAILURE);
		}

		snprintf(full_path, strlen(path_token) + strlen(command) + 2, "%s/%s", path_token, command);

		if (stat(full_path, &st) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execvp(full_path, args) == -1)
				{
					perror("ex_command");
					exit(EXIT_FAILURE);
				}
			}
			else if (pid < 0)
			{
				perror("ex_command");
				exit(EXIT_FAILURE);
			}
			else
			{
				do {
					waitpid(pid, &status, WUNTRACED);
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
			}

			free(full_path);
			return 1;
		}

		free(full_path);
		path_token = strtok(NULL, ":");
	}

	fprintf(stderr, "%s: command not found\n", command);

	return (1);
}

