#include "cmd.h"

void cmd_version(void* parameter)
{
		//show_version();
}

void cmd_clear(void* parameter)
{
		printf("\033[2J\033[H");
}

void cmd_help(void* parameter)
{
		printf("ps              	-List threads in the system\r\n");
		printf("version         	-show KY-Thread version information\r\n");
		printf("clear         		-clear the terminal screen\r\n");
		printf("reboot         		-Reboot System\r\n");		
}

void cmd_reboot(void* parameter)
{
		//__set_FAULTMASK(1);//关闭所有中断
		//NVIC_SystemReset();//复位函数	
}