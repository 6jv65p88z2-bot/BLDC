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

#define PERIPH_ADC_CLK	RCC_AHB_PERIPH_ADC
#define PERIPH_GPIOA_CLK	RCC_APB2_PERIPH_GPIOA
#define PERIPH_GPIOC_CLK	RCC_APB2_PERIPH_GPIOC
//函数声明

void bsp_adc_init(void);


#endif
