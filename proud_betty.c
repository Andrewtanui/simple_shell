#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    while (1)
    {
        printf("($)");
        nread = getline(&line, &bufsize, stdin);
        if (nread == -1)
            break;

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (fork() == 0)
        {
            if (execve(line, NULL, NULL) == -1)
            {
                perror("Error");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
        }
    }

    free(line);
    exit(EXIT_SUCCESS);
}

