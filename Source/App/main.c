/**
  ******************************************************************************
  * @file   main.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-03
  * @brief   main源文件
  ******************************************************************************
*/

#include "bsp_led.h"
#include "bsp_uart.h"
#include "bsp_key.h"
#include "bsp_uart_cb.h"
#include "bsp_pwm_cb.h"
#include "bsp_systick.h"
#include "bsp_opa.h"
#include "bsp_dac.h"
#include "bsp_pwm.h"

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
	
	bsp_uart_init(DEBUG_COM,115200,bsp_debug_com_irq_cb); //初始化串口[已经调通]
	bsp_uart_init(HOST_COMPUTER_COM,115200,bsp_host_computer_com_irq_cb); //初始化串口[已经调通]
	//uint8_t test_data[3] = {0x42,0x43,0x44};
	
	 //测试1：
	bsp_uart_init(RS485_COM, 115200, bsp_rs485_com_irq_cb);   //需要有usb转485的模块再用?
  	 
	//bsp_uart_send_data(RS485_COM,test_data,3);
  //printf("test\r\n");
	bsp_io_init();
	bsp_led_init();
	bsp_key_init();
	bsp_opa1_init();
	bsp_dac_init(300);
	
	bsp_pwm_init(bsp_pwm_irq_cb);	//初始化PWM
	
		
	bsp_led_ctrl(LED1, LED_ON);
	bsp_led_ctrl(LED2, LED_ON);
	bsp_led_ctrl(LED3, LED_ON);
	while(1)
	{
		// bsp_uart_send_data(HOST_COMPUTER_COM,test_data,3);  //
				// printf("test\r\n");	//测试成功1
				// bsp_delay_ms(1000);
		
		//bsp_uart_send_data(HOST_COMPUTER_COM,test_data,3); 
//		// printf("test\r\n");	//测试成功1
//		bsp_uart_send_data(RS485_COM,test_data,3);
		//bsp_delay_ms(1000);
		//bsp_led_ctrl(LED1,LED_TOGGLE);		//LED2翻转
		bsp_key_scan();
	}

}
