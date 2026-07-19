/**
  ******************************************************************************
  * @file    bsp_pwm_cb.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-14
  * @brief   pwm驱动源文件
  ******************************************************************************
*/

#include "bsp_pwm_cb.h"


static uint16_t test_num = 0;
/**
  ******************************************************************************
  * @brief  timer1的中断回调函数实现
  * @param  com:端口号
  * @retval None.
  ******************************************************************************/
void bsp_pwm_irq_cb(void)
{
	if(TIM_GetIntStatus(TIM1,TIM_INT_UPDATE) != RESET)
	{
		TIM_ClrIntPendingBit(TIM1,TIM_INT_UPDATE);
		test_num ++;
		if(test_num % 2 == 0)
		{
			//输出高电平
			ADC_TEST_IO_HIGH();
		}
		else
		{
			//输出低电平
			
			ADC_TEST_IO_LOW();
		}
	}
}
