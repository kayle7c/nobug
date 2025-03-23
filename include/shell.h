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
//shell�ṹ��
struct shell
{
		enum input_stat stat;
		
		char cmd[50];	//ָ������
	
		int position;     	//��ǰ�г���
		int curpos;     		//����λ��
};

#endif