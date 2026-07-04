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
#include "bsp_uart_cb.h"
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
	bsp_uart_init(DEBUG_COM,115200,bsp_debug_com_irq_cb); //初始化串口

  //测试1：uart2正常发送数据
  uint8_t test_data[3] = {0x41,0x42,0x43};	//测试成功1
 
	while(1)
	{
		// bsp_uart_send_data(DEBUG_COM,test_data,3);  //
		//		 printf("test\r\n");	//测试成功1
		//		 bsp_delay_ms(1000);
	}

}
