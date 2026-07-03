/**
  ******************************************************************************
  * @file   main.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-03
  * @brief   main源文件
  ******************************************************************************
*/

#include "bsp_uart.h"
#include "bsp_systick.h"
#include "misc.h"


/**
  ******************************************************************************
  * @brief  主函数入口地址
  * @param  None.	
  * @retval None.
  ******************************************************************************/
int main(void)
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//中断分组4
	bsp_systick_init();															//初始化系统滴答时钟
	bsp_uart_init(DEBUG_COM,115200,);
	while(1);

}