#include "shell.h"

/**
 * read_line - Read line input from the user.
 *
 * Return: Line input as a string.
 */
char *read_line(void)
{
	static char buffer[2048];
	static int buffer_pos;
	int c;

	while (1)
	{
		c = getchar();

		if (c == EOF || c == '\n')
		{
			buffer[buffer_pos] = '\0';
			buffer_pos = 0;
			return (strdup(buffer));
		}
		else
		{
			buffer[buffer_pos] = c;
			buffer_pos++;


			if (buffer_pos >= sizeof(buffer))
			{
				char *temp = malloc(sizeof(buffer) * 2);

				if (temp == NULL)
				{
					perror("read_line");
					exit(EXIT_FAILURE);
				}
				memcpy(temp, buffer, sizeof(buffer));
				free(buffer);
				buffer = temp;
			}
		}
	}
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
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
