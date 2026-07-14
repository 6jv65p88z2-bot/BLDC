/**
  ******************************************************************************
  * @file    bsp_pwm.h
  * @author  lbm
  * @version V1.0
  * @date    2026-07-13
  * @brief   pwm驱动头文件
  ******************************************************************************
*/



#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#include "n32g43x.h"

typedef struct
{
	void (*pwm_cb)(void);
}pwm_irq_cb_t;

extern pwm_irq_cb_t pwm_irq_cb;


void bsp_pwm_init(void (*irq_cb(void)));


#endif
