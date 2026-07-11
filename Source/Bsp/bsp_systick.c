/**
  ******************************************************************************
  * @file    bsp_systick.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-03
  * @brief   systick驱动源文件
  ******************************************************************************
*/

#include "bsp_systick.h"
volatile uint32_t systick_count;

/**
  ******************************************************************************
  * @brief  系统定时器初始化
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_systick_init(void)
{
	if(SysTick_Config(SystemCoreClock / 1000))
	{
		while(1);
	}
}
	
	
/**
  ******************************************************************************
  * @brief  系统定时器关闭
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_systick_disable(void)
{
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
}
	

/**
  ******************************************************************************
  * @brief  系统定时器时间获取
  * @param  None.
  * @retval systick_count:返回系统定时器时间
  ******************************************************************************/
uint32_t bsp_systick_time_get(void)
{
	return systick_count;
}
	
	/**
  ******************************************************************************
  * @brief  ms延时
  * @param  time：延时时间
  * @retval None.
  ******************************************************************************/
void bsp_delay_ms(uint32_t time)
{
	uint32_t temp = 0;
	temp = systick_count + time;
	while(systick_count <= temp);

}
