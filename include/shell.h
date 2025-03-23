#ifndef __SHELL_H
#define __SHELL_H

enum input_stat
{
		WAIT_NORMAL_KEY,   
		WAIT_DIR_KEY,			
		WAIT_FUNC_KEY,		
};
struct cmd_node
{
		char* name;
		int cmd_length;
	
		void       (*entry)(void *parameter);
		void       *parameter;
};
typedef struct cmd_node cmd_t; 
//shell结构体
struct shell
{
		enum input_stat stat;
		
		char cmd[50];	//指令内容
	
		int position;     	//当前行长度
		int curpos;     		//光标的位置
};

#endif