#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/zshell.h"
#include "include/debug.h"

char buffer[PAR_LEN];
int read_command(char **command,char **parameters)
{
    char* Res_fgets = fgets(buffer,COMMAND_LEN,stdin);
    if(Res_fgets == NULL)
    {
        printf("\n");
        exit(0);
    }		

    if(buffer[0] == '\0')
        return -1;
    char *pStart,*pEnd;
    int count = 0;
    int isFinished = 0;
    pStart = pEnd = buffer;
    while(isFinished == 0)
    {
        while((*pEnd == ' ' && *pStart == ' ') || (*pEnd == '\t' && *pStart == '\t'))
        {
            pStart++;
            pEnd++;
        }
/*
        if(*pEnd == '\0' || *pEnd == '\n')
        {
            if(count == 0)
                return -1;
            break;
        }
*/
        while(*pEnd != ' ' && *pEnd != '\0' && *pEnd != '\n')
            pEnd++;

        if(count == 0)
        {
            *command = pStart;
            parameters[0] = pStart;
            count += 1;
           debug_print("\ncommand:%s\n",*command);
        }
        else if(count <= PAR_LEN)
        {
			parameters[count] = pStart;
            count++;
        }
        else
        {
            break;
        }

        if(*pEnd == '\0' || *pEnd == '\n')
        {
            *pEnd = '\0';
            isFinished = 1;
        }
        else
        {
            *pEnd = '\0';
            pEnd++;
			pStart = pEnd;
        }
    }

    parameters[count + 1] = NULL;

    /*input analysis*/
    debug_print("input analysis:\n");
    debug_print("pathname:[%s]\ncommand:[%s]\nparameters:\ncount:%d\n",*command,parameters[0],count);
    int i;
    for(i=0;i<count;i++)
        debug_print("[%s]\n",parameters[i]);
	
    return count;
}
