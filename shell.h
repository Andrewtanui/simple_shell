#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOKEN_BUFSIZE 1024
#define TOKEN_DELIMITERS " \t\r\n\a"

char *read_line(void);
char **split_line(char *line);
int execute_command(char **args);

int ex_exit(void);
int ex_env(void);
int ex_cd(char **args);

extern char **environ;

char *get_environ_variable(const char *vari_name);
int set_environ_variable(const char *vari_name, const char *value);

#endif
