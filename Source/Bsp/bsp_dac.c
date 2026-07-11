/**
  ******************************************************************************
  * @file    bsp_dac.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-10
  * @brief   dac驱动源文件
  ******************************************************************************
*/
#include "bsp_dac.h"


/**
  ******************************************************************************
  * @brief  bsp_dac_rcc_config dac的时钟设置
  * @param  None.
  * @retval None.
  ******************************************************************************/
static void bsp_dac_rcc_config(void)
{
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC,ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA,ENABLE);
}

/**
  ******************************************************************************
  * @brief  bsp_dac_gpio_config dac的配置
  * @param  None.
  * @retval None.
  ******************************************************************************/
static void bsp_dac_gpio_config(void)
{
	GPIO_InitType GPIO_InitStructure;
	GPIO_InitStruct(&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
	GPIO_InitStructure.Pin = GPIO_PIN_4;
	GPIO_InitStructure.GPIO_Pull = GPIO_No_Pull;
	GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
}

/**
  ******************************************************************************
  * @brief  dac 配置
  * @param  None.
  * @retval None.
  ******************************************************************************/
static void bsp_dac_config(uint16_t dac_val)
{
	DAC_InitType DAC_InitStructure;
	DAC_InitStructure.BufferOutput = DAC_BUFFOUTPUT_DISABLE;//禁用 DAC 通道输出缓存
	DAC_InitStructure.LfsrUnMaskTriAmp = DAC_UNMASK_LFSRBIT0;  	//WaveGen设置为DAC_WAVEGEN_NONE后设置LfsrUnMaskTriAmp任意值始终为无效状态
	DAC_InitStructure.Trigger = DAC_TRG_SOFTWARE;			//DAC通过软件方式触发
	DAC_InitStructure.WaveGen = DAC_WAVEGEN_NONE;     	//禁用噪声和三角波
	DAC_Init(&DAC_InitStructure);
	
	DAC_Enable(ENABLE);
	bsp_delay_ms(100);	//等待DAC完全打开 tWAKEUP时间
	DAC_SetChData(DAC_ALIGN_R_12BIT,dac_val);		//1.0V   241mv  这个结果是测试出来的值吗？
	DAC_SoftTrgEnable(ENABLE);		//开启软件触发DAC	
	
}	
	
/**
  ******************************************************************************
  * @brief  dac 初始化
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_dac_init(uint16_t dac_val)
{
	bsp_dac_rcc_config();
	bsp_dac_gpio_config();
	bsp_dac_config(dac_val);
}
	
	
