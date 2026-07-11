/**
  ******************************************************************************
  * @file    bsp_dac.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-10
  * @brief   dac驱动源文件
  ******************************************************************************
*/


#ifndef __BSP_DAC_H__
#define __BSP_DAC_H__

#include "n32g43x.h"
#include "bsp_systick.h"

void bsp_dac_init(uint16_t dac_val);
#endif
