/**
  ******************************************************************************
  * @file    factory_check.c
  * @author  lbm
  * @version V1.0
  * @date    2026-08-6
  * @brief   出厂检测
  ******************************************************************************
  */
  
#include "function_check.h"
#include "bsp_uart_cb.h"
#include "bsp_dac.h"
#include "bsp_uart.h"

/**
  ******************************************************************************
  * @brief  出厂功能校验
  * @param  None.
  * @retval None.
  ******************************************************************************/
  
void factory_function_check(void)
{
	if(factory_func_check.overflow_sign)
	{
		bsp_dac_init(0);		//比较极端的数值，使得运放比较器OPA1 强制大于 DAC值，输出高电平，从而触发定时器刹车信号
		factory_func_check.overflow_sign = 0;
		printf("OVERFLOW Test\r\n");
	}
}
