/**
  ******************************************************************************
  * @file    bsp_opa.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-10
  * @brief   opa驱动源文件
  ******************************************************************************
*/

#include "bsp_opa.h"


/**
  ******************************************************************************
  * @brief  bsp_opa1_rcc_config opa的时钟设置
  * @param  None.
  * @retval None.
  ******************************************************************************/
static void bsp_opa1_rcc_config(void)
{
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_OPAMP,ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA,ENABLE);
}

/**
  ******************************************************************************
  * @brief  bsp_opa_gpio_config opa的时钟设置
  * @param  None.
  * @retval None.
  ******************************************************************************/
static void bsp_opa1_gpio_config(void)
{
	GPIO_InitType GPIO_InitStructure = {0};
	GPIO_InitStruct(&GPIO_InitStructure);
	
	/*
	OPAMP1:
		Vp:内部运放正端，PA7
		Vm:内部运放负端，悬空，不做配置。本次方案，负端选择PA3，此管脚不使用。软件上也不做配置
	*/
	OPAMP_SetVmSel(OPAMP1,OPAMPx_CS_VMSEL_FLOAT);		//Vm端悬空
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
	
	OPAMP_SetVpSel(OPAMP1,OPAMP1_CS_VPSEL_PA7);			//运放Vp的输入
	GPIO_InitStructure.Pin = GPIO_PIN_7;
	GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
	
	/*OPAMP1:OPA_OUT,PA2。运放输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
	GPIO_InitStructure.Pin = GPIO_PIN_2;
	GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
	GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
}


/**
  ******************************************************************************
  * @brief  opa1 配置
  * @param  None.
  * @retval None.
  ******************************************************************************/
static void bsp_opa1_conifg(void)
{
	OPAMP_InitType OPAMP_Initial;
	OPAMP_StructInit(&OPAMP_Initial);
	
	
	OPAMP_Initial.Gain = OPAMP_CS_PGA_GAIN_32;			//OPA放大倍数
	OPAMP_Initial.HighVolRangeEn = ENABLE;					//选择高电压区间;
	OPAMP_Initial.Mod = OPAMP_CS_PGA_EN;
	OPAMP_Initial.TimeAutoMuxEn = DISABLE;					//关闭定时器自动切换模式	

	OPAMP_Init(OPAMP1,&OPAMP_Initial);
	OPAMP_Enable(OPAMP1,ENABLE);
	
#if 0		//运放校准测试
	bsp_delay_ms(100);
	OPAMP_CalibrationEnable(OPAMP1,ENABLE);
	bsp_delay_ms(100);
	OPAMP_CalibrationEnable(OPAMP1,DISABLE);
#endif
	
}

  /**
  ******************************************************************************
  * @brief  bsp_opa_init opa初始化
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_opa1_init(void)
{
  //1.时钟初始化
  bsp_opa1_rcc_config();
  //2.配置GPIO
	bsp_opa1_gpio_config();
  //3.配置OPA参数
	bsp_opa1_conifg();

}
