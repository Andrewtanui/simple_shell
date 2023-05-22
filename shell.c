#include "shell.h"
/**
 * main - Entry point of the shell program
 *
 * Return: Always 0.
 */

int main(void)
{
    char *line;
    char **args;
    int stats;

    do {
        printf("#cisfun$ ");
        line = read_line();
        args = split_line(line);
        stats = exe_command(args);

        free(line);
        free(args);
    } while (stats);

    return 0;
}

