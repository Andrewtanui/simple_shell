#include "shell.h"

/**
 * execute_command - Execute a command using execlp
 * @command: The command to be executed
 *
 * Return: 1 to continue with the shell
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;

	if (command == NULL || command[0] == '\0')
		return (1);

	pid = fork();
	if (pid == 0)
	{
		if (execlp(command, command, NULL) == -1)
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

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *command;
	int status;

	do {
		printf("simple_shell$ ");
		command = read_line();

		if (command == NULL)
		{
			printf("\n");
			break;
		}

		char *trimmed_command = command;

		while (*trimmed_command == '\t')

			trimmed_command++;

		char *end = trimmed_command + strlen(trimmed_command) - 1;

		while (end > trimmed_command && *end == '\t')

			end--;

		*(end + 1) = '\0';
		status = execute_command(trimmed_command);

		free(command);
	} while (status);

	return (0);
}

