/**
  ******************************************************************************
  * @file    bsp_pwm_cb.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-14
  * @brief   pwm驱动源文件
  ******************************************************************************
*/


#ifndef __BSP_PWM_CB_H__
#define __BSP_PWM_CB_H__


#include "n32g43x.h"
#include "bsp_pwm.h"

#define ADC_TEST_TO_HIGH()	GPIO_SetBits(GPIOC,GPIO_PIN_5)
#define ADC_TEST_TO_LOW()	GPIO_ResetBits(GPIOC,GPIO_PIN_5)



void bsp_pwm_irq_cb(void);

#endif
