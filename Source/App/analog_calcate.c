/**
  ******************************************************************************
  * @file    analog_calcate.c
  * @author  lbm
  * @version V1.0
  * @date    2026-08-13
  * @brief   模拟量采集应用 源文件
  ******************************************************************************
*/


#include "analog_calcate.h"
#include "bsp_systick.h"
#include "bsp_adc_cb.h"
#include <math.h>
#include <stdio.h>

#define R23 33.0f		//分压网络中的上电阻
#define R30 3.0f		//分压网络中的下电阻

#define DIV_RATIO   (R30 / (R23 + R30))   // 分压系数 K = V_pin/V_bus


adc_voltage_val_e	adc_voltage_val;

/**
  ******************************************************************************
  * @brief  adc值计算  有添加滑动平均计算电压值
  * @param  None.
  * @retval None.
  ******************************************************************************/

/*
void adc_value_calculate(void)
{
	uint16_t adc_value = 0;
	float v_pin;			//经过分压网络后的引脚电压
	static uint32_t timeout = 0;
	static uint16_t adc_v_bus_buffer[8];		//母线电压滑动平均滤波缓冲区
	static uint32_t sum = 0;
	static uint8_t index = 0,cnt = 0;		//缓冲区下标 采集次数
	
	
	if(bsp_systick_time_get() - timeout > 50)		//每隔50ms采集一次
	{
		timeout = bsp_systick_time_get();
//		adc_value = adc_digital_val.v_bus;
//		v_pin = (float)adc_value /4095.0f * 3.3f;
//		adc_voltage_val.v_bus =  v_pin / DIV_RATIO;		//采集得到真正的数字量母线电压值 
		adc_v_bus_buffer[index] = adc_digital_val.v_bus;	// 每次进函数都累加一帧，滑动窗口 8 次
		index = (index + 1) & 0x07;	//滑动窗口
		cnt++;
		
		//printf("V_BUS:%.2fV\r\n",adc_voltage_val.v_bus);
	}
	
	if(cnt == 8)	//采集8次数据
	{
		
		for(uint8_t i = 0; i < cnt ; i ++ )
		{
			sum += adc_v_bus_buffer[i];
		}
		
		adc_value = sum >> 3;		//得到平均的ADC值
		v_pin = (float)adc_value /4095.0f * 3.3f;
		adc_voltage_val.v_bus =  v_pin / DIV_RATIO;		//采集得到真正的数字量母线电压值 
		
		cnt = 0;
		sum = 0;
		
		printf("ADC:0x%04X  V_BUS:%.2fV\r\n", (unsigned)adc_value, adc_voltage_val.v_bus);
	}
}
*/


/**
  ******************************************************************************
  * @brief  adc值计算  和视频的计算一致
  * @param  None.
  * @retval None.
  ******************************************************************************/
void adc_value_calculate(void)
{
	uint16_t adc_value = 0;
	float v_pin;		//经过分压网络后的引脚电压
	static uint32_t timeout = 0;
	
	if(bsp_systick_time_get() - timeout > 50)
	{
		timeout = bsp_systick_time_get();
		adc_value = adc_digital_val.v_bus;		//得到v_bus的模拟量
		v_pin = adc_value / 4095.0f * 3.3f;		
		adc_voltage_val.v_bus = v_pin / DIV_RATIO;		//得到真正的v_bus电压
		
		adc_value = adc_digital_val.temperature;	//得到temperature的模拟量
		float Rt = 0;		//NTC电阻(代计算)
		float R = 10000;	//10K固定阻值电阻
		float T0 = 273.15+ 25;	//转换为开尔文温度
		float B = 3450;
		float Ka = 273.15;		//K值
		float VR = 0;  //热敏两端的电压值(待计算)
		
		VR = 3.3 - (float)adc_value * 4095.f * 3.3f;		//转换为电压值
		Rt = (3.3 - VR) * 10000.0f / VR;		//得到Rt
		adc_voltage_val.temperature = 1 / ( 1 / T0 + log(Rt / R) / B) - Ka + 0.5;	//得到热敏电阻对应的真正温度
		printf("ADC:0x%04X  V_BUS:%.2fV\r\n,temperature:%.3fT", (unsigned)adc_value, adc_voltage_val.v_bus,adc_voltage_val.temperature);
	}
	
}

