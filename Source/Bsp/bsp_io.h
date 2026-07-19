/**
  ******************************************************************************
  * @file    bsp_io.h
  * @author  lbm
  * @version V1.0
  * @date    2026-07-19
  * @brief   io驱动头文件
  ******************************************************************************
*/
  
  

#ifndef __BSP_IO_H__
#define __BSP_IO_H__


#include "n32g43x.h"


#define ADC_TEST_IO_HIGH()	GPIO_SetBits(GPIOC, GPIO_PIN_5)
#define ADC_TEST_IO_LOW()	GPIO_ResetBits(GPIOC, GPIO_PIN_5)


void bsp_io_init(void);





#endif
