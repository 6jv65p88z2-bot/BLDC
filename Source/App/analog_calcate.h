/**
  ******************************************************************************
  * @file    analog_calcate.h
  * @author  lbm
  * @version V1.0
  * @date    2026-08-13
  * @brief   模拟量采集应用 头文件
  ******************************************************************************
*/

#ifndef __ANALOG_CALATE_H__
#define __ANALOG_CALATE_H__


#include "n32g43x.h"


typedef struct
{
	float v_bus;
	float temperature;
	float speed;
	
	float current;
	float bemf_u;
	float bemf_v;
	float bemf_w;
}adc_voltage_val_e;

void adc_value_calculate(void);


#endif
