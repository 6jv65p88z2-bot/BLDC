/**
  ******************************************************************************
  * @file    bsp_adc_value.h
  * @author  lbm
  * @version V1.0
  * @date    2026-08-13
  * @brief   母线电压等模拟量换算与滤波
  ******************************************************************************
*/

#ifndef __BSP_ADC_VALUE_H__
#define __BSP_ADC_VALUE_H__

#include "n32g43x.h"

/* ==================== 需根据原理图确认/修改的参数 ==================== */
#define ADC_REF_VOLTAGE      3.3f    /* ADC 参考电压，单位 V */
#define ADC_RESOLUTION       4095.0f /* 12位ADC满量程 */

/* 母线电压分压电阻（务必核对原理图！这里为示例值） */
#define VBUS_DIV_R1          100.0f  /* 上端电阻 kΩ */
#define VBUS_DIV_R2          10.0f   /* 下端电阻 kΩ */
/* 分压比 = R2/(R1+R2)，换算系数 = (R1+R2)/R2 */
#define VBUS_SCALE           ((VBUS_DIV_R1 + VBUS_DIV_R2) / VBUS_DIV_R2)

/* 一阶低通滤波系数：0~1，越小滤波越强 */
#define VBUS_FILTER_ALPHA    0.1f
/* ====================================================================== */

/* 采样电压换算结果 */
typedef struct
{
    float v_bus;        /* 母线电压，单位 V */
    float temperature;  /* 温度（预留） */
}adc_real_val_e;

extern adc_real_val_e adc_real_val;

void bsp_adc_value_init(void);
void bsp_adc_value_update(void);
float bsp_get_vbus_voltage(void);

#endif
