#ifndef _ZSHELL_H
#define _ZSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HOSTNAME_LEN 32
#define COMMAND_LEN 128
#define PAR_LEN 20

struct passwd* pwd;

int type_prompt(char* prompt);
int read_command(char **command,char **parameters);

#endif