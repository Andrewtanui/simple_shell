#include "shell.h"

/**
 * exe_exit - exit built-in command
 *
* Return: Returns 0 to exit shell
 */
int exe_exit(void)
{
    return 0;
}

/**
 * exe_env - env built-in command
 *
 * Return: Returns 1 to continue with shell
 */
int exe_env(void)
{
    extern char **environ;
    int i = 0;

    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }

    return 1;
}

