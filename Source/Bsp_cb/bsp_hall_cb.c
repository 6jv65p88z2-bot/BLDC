/**
  ******************************************************************************
  * @file    bsp_hall_cb.c
  * @author  lbm
  * @version V1.0
  * @date    2026-8-12
  * @brief   hall_cb回调函数源文件
  ******************************************************************************/
  
#include "bsp_hall_cb.h"

//函数声明
void bsp_hall_u_irq_cb(void (*bldc_sensor_algorithm_func_cb)(void));
void bsp_hall_v_irq_cb(void (*bldc_sensor_algorithm_func_cb)(void));
void bsp_hall_w_irq_cb(void (*bldc_sensor_algorithm_func_cb)(void));


/*定义指向U、V、W霍尔传感器中断回调函数的指针数组*/
void (*hall_uvw_irq_cb[3])(void (*bldc_sensor_algorithm_func_cb)(void)) = 
{bsp_hall_u_irq_cb,bsp_hall_v_irq_cb,bsp_hall_w_irq_cb};


/**
  ******************************************************************************
  * @brief  hall u相中断回调
  * @param  形参为一个函数指针.
  * @retval None.
  ******************************************************************************/
void bsp_hall_u_irq_cb(void (*bldc_sensor_algorithm_func_cb)(void))	
{
	if(RESET != EXTI_GetITStatus(EXTI_LINE1))
	{
		EXTI_ClrITPendBit(EXTI_LINE1);		//PC1
		bldc_sensor_algorithm_func_cb();	//调用这个函数指针
	}
}

/**
  ******************************************************************************
  * @brief  hall v相中断回调
  * @param  形参为一个函数指针.
  * @retval None.
  ******************************************************************************/
void bsp_hall_v_irq_cb(void (*bldc_sensor_algorithm_func_cb)(void))
{
	if(RESET != EXTI_GetITStatus(EXTI_LINE2))
	{
		EXTI_ClrITPendBit(EXTI_LINE2);		//PC2
		bldc_sensor_algorithm_func_cb();	//调用这个函数指针	
	}
}

/**
  ******************************************************************************
  * @brief  hall w相中断回调
  * @param  形参为一个函数指针.
  * @retval None.
  ******************************************************************************/
void bsp_hall_w_irq_cb(void (*bldc_sensor_algorithm_func_cb)(void))
{
	if(RESET != EXTI_GetITStatus(EXTI_LINE3))
	{
		EXTI_ClrITPendBit(EXTI_LINE3);		//PC3
		bldc_sensor_algorithm_func_cb();	//调用这个函数指针
	}
}
