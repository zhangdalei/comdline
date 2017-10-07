#include "parse.h"
#include <string.h>
/** 初始化参数结构体 */
void parse_info_init (struct parse_info* info)
{
	info->flag = 0;
    info->in_file = NULL;
    info->out_file = NULL;
	char* out_file = NULL;
}

/** 将读出的命令参数写入到参数结构中 */
int parseing (char** parameters, int *parnum, struct parse_info *info)
{
	int i;
	parse_info_init(info);
	// 后台运行
	if (!strcmp(parameters[*parnum - 1], "&")){
		info->flag = BACKGROUND;
		parameters[*parnum - 1] = NULL;
		printf("old parmum is %d\n", *parnum);
		*parnum = *parnum - 1;
		printf("new parmum is %d\n", *parnum);
	}
	for (i =0; i < *parnum; i++){
		if (!strcmp(parameters[i], ">")){
			info->flag = OUT_REDIRECT;
			info->out_file = parameters[i+1];
			parameters[i] = NULL;
			*parnum = i;
			i += 2;
		}else if (!strcmp(parameters[i], ">>")){
			info->flag = OUT_REDIRECT_APPEND;
			info->out_file = parameters[i+1];
			parameters[i] = NULL;
			*parnum = i;
			i += 2;
		}
	}
	
	return 1;
}