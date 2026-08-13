/**
  ******************************************************************************
  * @file    bsp_adc.h
  * @author  lbm
  * @version V1.0
  * @date    2026-07-28
  * @brief   adc驱动头文件
  ******************************************************************************
*/


#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "n32g43x.h"
#include "stdio.h"

#define PERIPH_ADC_CLK	RCC_AHB_PERIPH_ADC
#define PERIPH_GPIOA_CLK	RCC_APB2_PERIPH_GPIOA
#define PERIPH_GPIOC_CLK	RCC_APB2_PERIPH_GPIOC

typedef struct
{
	void (*adc_cb)(void (*u_formal_param)(void));
	void (*formal_param)(void);
}adc_irq_cb_t;

extern adc_irq_cb_t adc_irq_cb;		//给中断函数去使用这个结构体


//函数声明
void bsp_adc_init(void);


#endif
