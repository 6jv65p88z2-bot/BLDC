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

#define R23 33.0f		//分压网络中的上电阻
#define R30 3.0f		//分压网络中的下电阻

#define DIV_RATIO   (R30 / (R23 + R30))   // 分压系数 K = V_pin/V_bus


adc_voltage_val_e	adc_voltage_val;

/**
  ******************************************************************************
  * @brief  adc值计算
  * @param  None.
  * @retval None.
  ******************************************************************************/
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