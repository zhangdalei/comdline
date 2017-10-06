#ifndef _ZSHELL_H
#define _ZSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HOSTNAME_LEN 32
#define COMMAND_LEN 128
#define PAR_LEN 20
#define MAXPIDTABLE 1024

#define STRUCT_PARSE_INFO
#define BACKGROUND 			1
#define IN_REDIRECT 		2
#define OUT_REDIRECT 		4
#define OUT_REDIRECT_APPEND	8

struct passwd* pwd;

int type_prompt(char* prompt);
int read_command(char **command,char **parameters);

typedef struct parse_info 
{
    int flag;
    char* in_file;
    char* out_file;
}parse_info;

#endif