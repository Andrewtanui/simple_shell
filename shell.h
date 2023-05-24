#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

extern char **environ;

char *read_line(void);
char **split_line(char *line);
int ex_command(char **args);

int ex_exit(void);
int ex_env(void);
int ex_cd(char **args);

char *get_environ_variable(const char *vari_name);
int set_environ_variable(const char *vari_name, const char *value);

#endif
