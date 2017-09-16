#include <pwd.h>
#include <sys/types.h>
#include "include/zshell.h"

int type_prompt(char* prompt)
{
	char* pathname = NULL;
	uid_t uid;
	char hostname[HOSTNAME_LEN];
	uid = getuid();
	pwd = getpwuid(uid);
	if(gethostname(hostname, HOSTNAME_LEN)==0)
		sprintf(prompt,"[zshell]%s@%s:",pwd->pw_name, hostname);
	else
		sprintf(prompt,"[zshell]%s@unknown:",pwd->pw_name);
	pathname = getcwd(NULL, 0);
	sprintf(prompt,"%s%s",prompt, pathname);
	if(uid == 0)
		sprintf(prompt,"%s# ",prompt);
	else 
		sprintf(prompt,"%s$ ",prompt);
	free(pathname);
	return 0;
}
/*
int main()
{
	char prompt[512];
	type_prompt(prompt);
	printf("%s\n",prompt);
	return 0;
}
*/