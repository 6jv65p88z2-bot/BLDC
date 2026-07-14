/**
  ******************************************************************************
  * @file    bsp_timer.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-13
  * @brief   timer驱动源文件
  ******************************************************************************
*/


#include "bsp_timer.h"


/**
  ******************************************************************************
  * @brief  bsp_timer_rcc_config timer的时钟设置		使用TIMER1高级定时器
  * @param  None.
  * @retval None.
  ******************************************************************************/
static void bsp_timer8_rcc_config(void)
{
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8,ENABLE);	//开启TIM1和GPIOC的时钟
	
}
  
void bsp_timer8_init(void)
{
	bsp_timer8_rcc_config();
//	bsp_timer_gpio_config();
//	bsp_timer_config();
	
}