#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */
int main(void)
{
    char line[BUFFER_SIZE];
    pid_t pid;
    pid = fork();

    while (1)
    {
        printf("$ ");

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        line[strcspn(line, "\n")] = '\0';

        if (pid == (pid_t)-1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (execlp(line, line, NULL) == -1)
            {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
        }
    }

    exit(EXIT_SUCCESS);
}
