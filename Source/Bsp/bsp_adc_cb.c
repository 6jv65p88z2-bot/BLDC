/**
  ******************************************************************************
  * @file    bsp_adc_cb.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-28
  * @brief   adc驱动源文件
  ******************************************************************************
*/

#include "bsp_adc_cb.h"
#include "bsp_io.h"

extern volatile uint16_t ADC_RegularConvertedValueTab[3];
extern volatile uint16_t ADC_InjectConvertedValueTab[4];

adc_digital_val_e adc_digital_val;
uint32_t ttt_cnt;		//计数

/**
  ******************************************************************************
  * @brief  adc中断回调
  * @param  
  * @retval None.
  ******************************************************************************/
void bsp_adc_irq_cb(void)
{
	if(ADC_GetIntStatus(ADC,ADC_INT_JENDC) == SET)		//如果注入通道转换完成
	{
		ADC_TEST_IO_HIGH();
		ADC_ClearFlag(ADC,ADC_FLAG_JENDC);		//清楚注入通道转换完成标志位
		
		//读取注入通道转换的值
		ADC_InjectConvertedValueTab[0] = ADC_GetInjectedConversionDat(ADC,ADC_INJ_CH_1);		//Current->OPA->OPAOUT:PA2
		ADC_InjectConvertedValueTab[1] = ADC_GetInjectedConversionDat(ADC,ADC_INJ_CH_2);		//BEMF_U
		ADC_InjectConvertedValueTab[2] = ADC_GetInjectedConversionDat(ADC,ADC_INJ_CH_3);		//BEMF_V
		ADC_InjectConvertedValueTab[3] = ADC_GetInjectedConversionDat(ADC,ADC_INJ_CH_4);		//BEMF_W
		//获取规则通道转换的值
		adc_digital_val.v_bus = ADC_RegularConvertedValueTab[0];
		adc_digital_val.temperature = ADC_RegularConvertedValueTab[1];
		adc_digital_val.speed = ADC_RegularConvertedValueTab[2];
		
		adc_digital_val.current = ADC_InjectConvertedValueTab[0];
		adc_digital_val.bemf_u = ADC_InjectConvertedValueTab[1];
		adc_digital_val.bemf_v = ADC_InjectConvertedValueTab[2];
		adc_digital_val.bemf_w = ADC_InjectConvertedValueTab[3];
		
		//通过软件触发的方式启动规则通道ADC转换
		ADC_EnableSoftwareStartConv(ADC,ENABLE);
		ADC_TEST_IO_LOW();
		//计数器+1
		ttt_cnt++;
	}
}
