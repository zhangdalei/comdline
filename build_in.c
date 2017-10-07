#include "zshell.h"
#include <pwd.h>
#include <sys/types.h>
#include <string.h>
#include "history.h"

int build_in(const char* com, char** par) {
	char *path = NULL;
	if(!strcmp(com, "quit") || !strcmp(com, "exit") || !strcmp(com, "q"))
		exit(1);
	else if(!strcmp(com, "cd")) {
		if(par[1][0] == '~') {
			path = pwd->pw_dir;
		}
		else{
			path = par[1];
		}
		chdir(path);
		return 1;
	}else if (!strcmp(com, "history")){
		list_history();
		return 1;
	}
	else {
		return 0;
	}
}