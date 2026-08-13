/**
  ******************************************************************************
  * @file    bsp_adc_cb.h
  * @author  lbm
  * @version V1.0
  * @date    2026-07-28
  * @brief   adc驱动源文件
  ******************************************************************************
*/
#ifndef __BSP_ADC_CB_H__
#define __BSP_ADC_CB_H__

#include "n32g43x.h"



typedef struct
{
	uint16_t v_bus;					//母线电压
	uint16_t temperature;			//温度
	uint16_t speed;					//电机的速度
	
	uint16_t current;				//电流环的电流
	uint16_t bemf_u;				//反电动势U
	uint16_t bemf_v;				//反电动势V
	uint16_t bemf_w;				//反电动势W
	
}adc_digital_val_e;


extern adc_digital_val_e adc_digital_val;

void bsp_adc_irq_cb(void);








#endif

