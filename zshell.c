#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "zshell.h"
#include "debug.h"
// 保存后台进程pid
pid_t BPTable[MAXPIDTABLE] = {0};

extern int build_in(const char* com, char** par);
static void process();
int numbackpro = 0;

int main()
{
		process();	
		return 0;
}
// 后台子进程死亡处理
void sig_handler(int sig)
{
    pid_t pid;
    int i;
	if (numbackpro > 0)
	{
		for(i = 0; i < MAXPIDTABLE; i++)
			if(BPTable[i] != 0) //only handler the background processes
			{
				pid = waitpid(BPTable[i],NULL,WNOHANG);
				if(pid > 0)
				{
					printf("process %d exited.\n",pid);
					BPTable[i] = 0; //clear
				}
				else if(pid < 0)
				{
					if(errno != ECHILD)
						perror("waitpid error");
				}
			 }
    }
}

static void process()
{
	pid_t pid,ChdPid;
	int out_fd = 0;
	int status;
	int parnum;
	parse_info info;
	char prompt[HOSTNAME_LEN];
	char *command = NULL;
	char *parameters[PAR_LEN];
	char *com;
	
	// 接收子进程死亡信号
	if(signal(SIGCHLD,sig_handler) == SIG_ERR)
        perror("signal() error");
	
	while(1)
	{
		type_prompt(prompt);
		fprintf(stdout, "%s",prompt);
		parnum = read_command(&command, parameters);
		
		/** 命令解析 */
		parseing (parameters, &parnum, &info);
		
		com = command;
		// 内建命令处理 cd
		if (build_in(com, parameters))
			continue;
		debug_print("command:[%s]\nparameters:\ncount:%d\n",com,parnum);
		#ifdef DEBUG
		int i;
		for(i=0;i<parnum;i++)
			debug_print("[%s]\n",parameters[i]);
		#endif
		if(!strcmp(com, "")){
			//printf("-----------------------");
			continue;
		}
		pid = fork();
		// 子线程，使用exec函数启用新的程序
		if(pid == 0) {
			debug_print("child process is running.\n");
			int i =0 ;
			char *ls_argv[PAR_LEN] = {""};
			// 将标准输出重定向到out_fd
			if (info.flag == OUT_REDIRECT){
				out_fd = open(info.out_file, O_WRONLY|O_CREAT|O_TRUNC, 0666);
				close (1);
				dup2 (out_fd, 1);
				close (out_fd);
			}else if (info.flag == OUT_REDIRECT_APPEND){
				out_fd = open(info.out_file, O_WRONLY|O_CREAT|O_APPEND, 0666);
				close (1);
				dup2 (out_fd, 1);
				close (out_fd);
			}
			for(i; i < parnum; i++){
				ls_argv[i] = parameters[i];
			}
			if(execvp(com, ls_argv) < 0){
				perror("execvp error.\n");
				exit(0);
			}
		}else if(pid > 0) {
			debug_print("parent process is running child is: %d\n",pid);
			if (info.flag & BACKGROUND){
				numbackpro++;
				int i = 0;
				for (i = 0; i < MAXPIDTABLE; i++) {
					if (BPTable[i] == 0)
						BPTable[i] = pid;	// 将后台子进程注册到数组中
					if (i == MAXPIDTABLE)
						perror("Too much background processes\nThere will be zombine process");
				}
				debug_print ("background process.\n");
			}
			else 
				waitpid(pid, &status, 0);
		}else if(pid < 0) 
			exit(0);
	}
}






