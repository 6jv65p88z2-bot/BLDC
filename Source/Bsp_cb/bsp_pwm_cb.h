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
#include "bsp_io.h"


void bsp_pwm_irq_cb(void);			//TIM1的更新中断 回调函数
void bsp_pwm_irq_bk_cb(void);		//TIM1的刹车中断 回调函数

#endif
