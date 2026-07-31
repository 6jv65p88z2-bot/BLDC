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



#define PWM_PERIOD_MAX			(2700)		//pwm period最大值




typedef struct
{
	void (*pwm_cb)(void);			//TIM1的PWM
	void (*pwm_bk_cb)(void);		//TIM7的配置 用来配置OUTPUT CTRL
}pwm_irq_cb_t;

extern pwm_irq_cb_t pwm_irq_cb;


//void bsp_pwm_init(void (*irq_cb)(void));
void bsp_pwm_init(void (*irq_bk_cb)(void),void (*irq_cb)(void));
void bsp_all_pwm_open(void);
void bsp_all_pwm_close(void);
void bsp_pwm_set_duty(uint16_t duty);


#endif
