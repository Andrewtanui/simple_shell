#ifndef SIMPLE_SHELL_H_
#define SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define BUFA_SIZE 1024
#define BUF_SIZE_WRITE 1024
#define BUFA_FLUSHA -1

#define NORMAL_CMD	0
#define OR_CMD		1
#define AND_COMMAND	2
#define CHAIN_COMMAND 3

#define LOWERCASE_CONVERTER	1
#define UNSIGNED_CONVERSION	2

#define USING_GETLINE 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAXIMUM	4096

extern char **environ;


/**
 * struct liststring - singly linked list
 * @num: number field
 * @str: string
 * @next: points next node
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} listing_t;

/**
 * struct passinformation - arguements to pass into a function
 * @arg: string from getline with args
 * @argv: array of strings from arg
 * @path: string path current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error for exit func
 * @linecount_flag: count this line of input
 * @fname: filename of prog
 * @env: environ copy
 * @environ: modified copy of environ
 * @history: history node
 * @alias: alias node
 * @env_changed: if environ was changed
 * @status: return status last exec'd
 * @cmd_buf: address of pointer to cmd_buf
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd which to read line
 * @histcount: history count
 */
typedef struct passinformation
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	listing_t *env;
	listing_t *history;
	listing_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} information_t;

#define INFORMATION_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - builtin string
 * @type: command flag for the builtin
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(information_t *);
} bultin_t;


int hsh(information_t *, char **);
int find_bultn(information_t *);
void find_command(information_t *);
void fork_command(information_t *);

int is_command(information_t *, char *);
char *duplicte_characters(char *, int, int);
char *fnd_path(information_t *, char *, char *);


void _errputs(char *);
int _errputchar(char);
int _puttfd(char c, int fd);
int _puttsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *start_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdupli(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void fffre(char **);
void *_realloc(void *, unsigned int, unsigned int);

int befree(void **);

int interact(information_t *);
int is_delimeter(char, char *);
int _isalpha(int);
int _atoi(char *);

int _erroratoi(char *);
void print_err(information_t *, char *);
int print_dec(int, int);
char *convert_nmb(long int, int, int);
void remove_cmmnt(char *);

int _shell_exit(information_t *);
int _me_cd(information_t *);
int _me_help(information_t *);

int _myhisto(information_t *);
int _me_alias(information_t *);

ssize_t get_inpt(information_t *);
int _get_line(information_t *, char **, size_t *);
void sigintHandler(int);

void clear_information(information_t *);
void set_information(information_t *, char **);
void free_information(information_t *, int);

char *_get_env(information_t *, const char *);
int _me_env(information_t *);
int _me_setenv(information_t *);
int _me_unsetenv(information_t *);
int pop_env_list(information_t *);

char **get_environ(information_t *);
int _unset_env(information_t *, char *);
int _set_env(information_t *, char *, char *);

char *get_histo_file(information_t *info);
int write_histo(information_t *info);
int read_histo(information_t *info);
int build_histo_lst(information_t *info, char *buf, int linecount);
int renmb_histo(information_t *info);

listing_t *_node_ad(listing_t **, const char *, int);
listing_t *_nod_end_ad(listing_t **, const char *, int);
size_t prnt_lst_string(const listing_t *);
int del_nod_indx(listing_t **, unsigned int);
void free_lst(listing_t **);

size_t lst_length(const listing_t *);
char **list_to_strings(listing_t *);
size_t prnt_lst(const listing_t *);
listing_t *nod_start_wth(listing_t *, char *, char);
ssize_t gt_nod_indx(listing_t *, listing_t *);

int chains(information_t *, char *, size_t *);
void chn_chks(information_t *, char *, size_t *, size_t, size_t);
int rplc_alias(information_t *);
int rplc_var(information_t *);
int rplc_str(char **, char *);

#endif
