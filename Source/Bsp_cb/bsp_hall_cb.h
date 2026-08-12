/**
  ******************************************************************************
  * @file    bsp_hall_cb.h
  * @author  lbm
  * @version V1.0
  * @date    2026-8-12
  * @brief   hall_cb回调函数头文件
  ******************************************************************************/
  
#ifndef __BSP_HALL_CB_H__
#define __BSP_HALL_CB_H__


#include "n32g43x.h"


extern void (*hall_uvw_irq_cb[3])(void (*bldc_sensor_algorithm_func_cb)(void));
#endif

