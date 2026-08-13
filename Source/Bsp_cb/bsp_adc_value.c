/**
  ******************************************************************************
  * @file    bsp_adc_value.c
  * @author  lbm
  * @version V1.0
  * @date    2026-08-13
  * @brief   母线电压等模拟量换算与滤波
  ******************************************************************************
*/

#include "bsp_adc_value.h"
#include "bsp_adc_cb.h"

adc_real_val_e adc_real_val;

static float vbus_filtered = 0.0f;  /* 滤波后的母线电压 */

/**
  ******************************************************************************
  * @brief  采样值换算初始化
  * @retval None.
  ******************************************************************************/
void bsp_adc_value_init(void)
{
    vbus_filtered = 0.0f;
    adc_real_val.v_bus = 0.0f;
    adc_real_val.temperature = 0.0f;
}

/**
  ******************************************************************************
  * @brief  把ADC数字量换算成实际母线电压，并做一阶低通滤波
  * @note   数字量 -> 引脚电压 -> 母线电压
  *         V_pin = adc * Vref / 4095
  *         V_bus = V_pin * (R1+R2)/R2
  * @retval None.
  ******************************************************************************/
void bsp_adc_value_update(void)
{
    float v_pin;
    float v_bus_raw;

    /* 1. 数字量转引脚电压 */
    v_pin = (float)adc_digital_val.v_bus * ADC_REF_VOLTAGE / ADC_RESOLUTION;

    /* 2. 引脚电压还原为母线电压 */
    v_bus_raw = v_pin * VBUS_SCALE;

    /* 3. 一阶低通滤波：y(k) = y(k-1) + alpha * (x(k) - y(k-1)) */
    vbus_filtered = vbus_filtered
                    + VBUS_FILTER_ALPHA * (v_bus_raw - vbus_filtered);

    adc_real_val.v_bus = vbus_filtered;
}

/**
  ******************************************************************************
  * @brief  获取当前母线电压
  * @retval 母线电压值，单位 V
  ******************************************************************************/
float bsp_get_vbus_voltage(void)
{
    return adc_real_val.v_bus;
}
