#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

char *read_line(void);
char **split_line(char *line);
int exe_command(char **args);

int exe_exit(void);
int exe_env(void);

char *get_environ_variable(const char *vari_name);
int set_environ_variable(const char *vari_name, const char *value);

#endif /* SHELL_H */
