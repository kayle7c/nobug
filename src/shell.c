#include "shell.h"
#include "cmd.h"

int cmd_table[CMD_NUM_MAX];
int current_cmd_num=0;

struct shell my_shell;
struct shell *shell = &my_shell;

struct ringbuffer shell_ringbuffer;
char ringbuffer[200];

char shell_getchar()
{
		char ch=-1;

		if(!ringbuffer_isempty(&shell_ringbuffer))
		{
				ringbuffer_getchar(&shell_ringbuffer,&ch);
		}
		else
		{
				ky_thread_delay_ms(10);
		}
		return ch;
}

void shell_match(char *cmd,ky_size_t length)	
{
		for(int i=0;i<current_cmd_num;i++)
		{
				if(length == cmd_table[i].cmd_length)
				{
						if(ky_strcmp(cmd,cmd_table[i].name))
						{
								cmd_table[i].entry(cmd_table[i].parameter);
								printf("ky />");
								return ;
						}
				}
		}
		printf("cmd not found!");
		printf("\r\n");
		printf("ky />");
#endif 
}

ky_size_t shell_auto_complete(char* cmd,ky_size_t length)
{
		int complete_num=0;
		int cmd_index=0;
		int cmd_indexs[10];
		int cmd_num=0;
		for(int i=0;i<current_cmd_num;i++)
		{
				if(ky_strcmp(cmd,cmd_table[i].name))
				{
						complete_num++;
						cmd_index=i;
						if(cmd_num<10)		cmd_indexs[cmd_num++]=i;
				}
		}
		if(complete_num==0)
		{
				return 0;
		}
		else if(complete_num==1)
		{
				for(int j=0;j<length;j++)
				{
						printf("\b \b");
				}
				printf("%s",cmd_table[cmd_index].name);
				ky_strncpy(shell->cmd,cmd_table[cmd_index].name,cmd_table[cmd_index].cmd_length);
				shell->position=cmd_table[cmd_index].cmd_length;
		}
		else
		{
				printf("\r\n");
				for(int i=0;i<cmd_num;i++)
				{
						printf("%s ",cmd_table[cmd_indexs[i]].name);
				}		
				printf("\r\n");
				printf("ky />");	
		}
}

void shell_thread_entry()
{
		int ch;
		shell->current_history=0;
		shell->history_cnt=0;
	
		//up key  : 0x1b 0x5b 0x41
    //down key: 0x1b 0x5b 0x42
    //right key:0x1b 0x5b 0x44
    //left key: 0x1b 0x5b 0x43
		printf("ky />");
		while(1)
		{
				ch=shell_getchar();
				if(ch==0XFF)
				{
						continue;
				}
//***************************************************************
//*********************�������********************************
#if 0   //�����δ����
				if(ch==0x1b)
				{
						shell->stat=WAIT_DIR_KEY;
						continue;
				}
				else if(shell->stat==WAIT_DIR_KEY)
				{
						if(ch==0x5b)
						{	
								shell->stat=WAIT_FUNC_KEY;
								continue;
						}
						shell->stat=WAIT_NORMAL_KEY;
				}
				else if(shell->stat==WAIT_FUNC_KEY)
				{
						shell->stat=WAIT_NORMAL_KEY;
						if(ch==0x41)
						{
								printf("%d",shell->current_history);
								if(shell->current_history>0)
								{
										shell->current_history--;
										printf("%s",shell->history[shell->current_history]);
										memcpy(&shell->cmd,
													 &shell->history[shell->current_history],
													 ky_strlen(shell->history[shell->current_history]));
								}
								//printf("up");
								continue;
						}
						else if(ch==0x42)
						{
								//printf("down");
								if(shell->current_history<shell->history_cnt)
								{
									shell->current_history++;
									printf("%s",shell->history[shell->current_history]);
									memcpy(&shell->cmd,
													 &shell->history[shell->current_history],
													 ky_strlen(shell->history[shell->current_history]));
								}
								continue;

						}
						else if(ch==0x43)
						{
								if(shell->curpos<shell->position)
								{
										printf("%c",shell->cmd[shell->curpos]);
										shell->curpos++;
								}
								//printf("left");
								continue;
						}
						else if(ch==0x44)
						{
								if(shell->curpos>0)
								{
										printf("\b");
										shell->curpos--;
								}
								continue;
						}
				}
#endif
//***************************************************************
//*********************����tab��*********************************
				if(ch=='\t')
				{
						shell_auto_complete(shell->cmd,shell->position);
						continue;
				}
//***************************************************************
//*********************�����˸��********************************
				else if(ch==0x08)
				{
						//���λ���ڿ�ͷ
						if(shell->curpos==0)
						{
								continue;
						}
						shell->position--;
						shell->curpos--;
						printf("\b \b");   //������
						shell->cmd[shell->curpos]=0;
						continue;
				}
//***************************************************************
//*********************����س���********************************				
				else if(ch=='\r'||ch=='\n')
				{
						printf("\r\n");
						if(shell->position==0 || shell->position>=KY_SHELL_LENGSH)
						{
								printf("ky />");
								continue;
						}
						memcpy(&shell->history[shell->current_history],
								   &shell->cmd,
									 ky_strlen(shell->cmd));
						shell->history_cnt++;
						shell->current_history=shell->history_cnt;
						shell_match(shell->cmd,shell->position);					
						memset(shell->cmd,0,sizeof(shell->cmd));
						shell->position=0;
						shell->curpos=0;
						continue;
				}
////***************************************************************
////*********************�������ַ�******************************		
				if(shell->curpos<shell->position)
				{
						ky_memmove(&shell->cmd[shell->curpos+1],
											 &shell->cmd[shell->curpos],
											 shell->position-shell->curpos);
						shell->cmd[shell->curpos]=ch;
						printf("%s",&shell->cmd[shell->curpos]);
						for(int i=shell->curpos;i<shell->position;i++)
						{
								printf("\b");
						}
				}
				else
				{
						shell->cmd[shell->position]=ch;
						printf("%c",ch);
						shell->position++;
						shell->curpos++;
				}
		}
}


void cmd_list_add(char* name,
									 ky_size_t length,
									 void (*entry)(void *parameter),
									 void *parameter)
{
			cmd_table[current_cmd_num].name=name;
			cmd_table[current_cmd_num].cmd_length=length;
			cmd_table[current_cmd_num].entry=entry;
			cmd_table[current_cmd_num].parameter=parameter;
	
			current_cmd_num++;
}

void system_cmd_init()
{
		cmd_list_add("version",7,cmd_version,KY_NULL);
		cmd_list_add("clear",5,cmd_clear,KY_NULL);
		cmd_list_add("ps",2,cmd_ps,KY_NULL);
		cmd_list_add("reboot",6,cmd_reboot,KY_NULL);
		cmd_list_add("help",4,cmd_help,KY_NULL);
}		
