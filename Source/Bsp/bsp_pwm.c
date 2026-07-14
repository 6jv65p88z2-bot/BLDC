/**
  ******************************************************************************
  * @file    bsp_pwm.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-14
  * @brief   pwm驱动源文件
  ******************************************************************************
*/


#include "bsp_pwm.h"
#include <stdio.h>
pwm_irq_cb_t pwm_irq_cb = {NULL};
/**
  ******************************************************************************
  * @brief  pwm时钟初始化
  * @param  None
  * @retval None.
  ******************************************************************************/
static void bsp_pwm_rcc_config(void)
{
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1,ENABLE);
}


/**
  ******************************************************************************
  * @brief  pwm的io初始化
  * @param  None
  * @retval None.
  ******************************************************************************/
static void bsp_pwm_io_config(void)
{
	
}


/**
  ******************************************************************************
  * @brief  pwm的tiemr1配置
  * @param  None
  * @retval None.
  ******************************************************************************/
static void bsp_pwm_config(void)
{
	TIM_TimeBaseInitType TIM_TimBaseInitStructure;
	NVIC_InitType NVIC_InitStructure;
	
	TIM_InitTimBaseStruct(&TIM_TimBaseInitStructure);
	
	TIM_TimBaseInitStructure.ClkDiv = TIM_CLK_DIV1;								//分频系数
	TIM_TimBaseInitStructure.CntMode = TIM_CNT_MODE_UP;							//计数模式
	TIM_TimBaseInitStructure.Period = 1000;										//计数周期（自动重装载值）		计数1000次就是1ms 
	TIM_TimBaseInitStructure.Prescaler = 108 - 1;  								//预分频值 1MHZ = 1000 000hz  T = 1/f = 1/1000000 = 0.000001s = 1us 也就是1us计数1次
	TIM_TimBaseInitStructure.RepetCnt = 0;										//重复计数
	
	TIM_InitTimeBase(TIM1,&TIM_TimBaseInitStructure);
	TIM_ConfigInt(TIM1,TIM_INT_UPDATE,ENABLE);									//设置定时器的中断，使能
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 16;					//抢占优先级(主)
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;							//响应优先级(子)
	
	NVIC_Init(&NVIC_InitStructure);
	//定时器1开启
	TIM_Enable(TIM1,ENABLE);													//使能TIM1
}


/**
  ******************************************************************************
  * @brief  pwm初始化 timer1
  * @param  irq_cb:timer 的中断回调指针
  * @retval None.
  ******************************************************************************/
void bsp_pwm_init(void (*irq_cb(void)))
{
	if(irq_cb == NULL)
	{
		while(1);//空指针，直接进入死循环
	}
	pwm_irq_cb.pwm_cb = irq_cb;
	
	bsp_pwm_rcc_config();
	bsp_pwm_io_config();
	bsp_pwm_config();	
}
