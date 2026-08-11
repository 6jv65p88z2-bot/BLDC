/**
  ******************************************************************************
  * @file    bsp_hall.c
  * @author  lbm
  * @version V1.0
  * @date    2026-8-11
  * @brief   hall头文件
  ******************************************************************************/

#ifndef __BSP_HALL_H
#define __BSP_HALL_H

#include "n32g43x.h"

typedef struct
{
	void (*hall_u_cb)(void (*u_formal_param)(void));
	void (*hall_v_cb)(void (*v_formal_param)(void));
	void (*hall_w_cb)(void (*w_formal_param)(void));
	
	void (*formal_param)(void);
}hall_irq_cb_t;




//函数声明
void bsp_hall_init(void( *irq_cb[3])(void (*formal_param)(void)),void (*formal_param)(void));

#endif
