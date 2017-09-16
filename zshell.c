#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "include/zshell.h"
#include "include/debug.h"

int process();

int main()
{
	while(1){
		process();
	}
	return 0;
}

int process()
{
	pid_t pid;
	int status;
	int parnum;
	char prompt[HOSTNAME_LEN];
	char *command = NULL;
	char *parameters[PAR_LEN];
	char *com;
	
	type_prompt(prompt);
	fprintf(stdout, "%s",prompt);
	parnum = read_command(&command,parameters);
	com = command;
	
	debug_print("command:[%s]\nparameters:\ncount:%d\n",com,parnum);
	if(!strcmp(com, "qute") || !strcmp(com, "q"))
		exit(1);
/*
	int i;
    for(i=0;i<parnum;i++)
        debug_print("[%s]\n",parameters[i]);
*/
	pid = fork();
	if(pid == 0) {
		debug_print("child process is running.\n");
		int i =0 ;
		char *ls_argv[PAR_LEN] = {""};
		for(i; i < parnum; i++){
			ls_argv[i] = parameters[i];
		}
		if(execvp(com, ls_argv) < 0){
			perror("execvp error.\n");
			exit(0);
		}
	}else if(pid > 0) {
		printf("parent process is running child is: %d\n",pid);
		waitpid(pid, &status, 0);
	}else if(pid < 0) 
		exit(0);

	return 0;
}






