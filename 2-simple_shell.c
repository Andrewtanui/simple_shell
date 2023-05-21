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

    while (1)
    {
        pid_t pid;

        printf("$ ");

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        line[strcspn(line, "\n")] = '\0';

        pid = fork();
        if (pid == (pid_t)-1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            char *args[BUFFER_SIZE];
            int i = 0;

            char *token = strtok(line, " ");
            while (token != NULL)
            {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
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

