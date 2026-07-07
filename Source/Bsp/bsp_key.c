#include "bsp_led.h"
#include <stdio.h>

static gpio_struct_t led_config[] = 
{
	LED1,GPIOC,{GPIO_PIN_15,GPIO_DC_2mA,GPIO_Slew_Rate_High,GPIO_No_Pull,GPIO_Mode_Out_OD,GPIO_NO_AF},
	LED2,GPIOC,{GPIO_PIN_14,GPIO_DC_2mA,GPIO_Slew_Rate_High,GPIO_No_Pull,GPIO_Mode_Out_OD,GPIO_NO_AF},
	LED2,GPIOC,{GPIO_PIN_13,GPIO_DC_2mA,GPIO_Slew_Rate_High,GPIO_No_Pull,GPIO_Mode_Out_OD,GPIO_NO_AF},
	LEDMAX,(GPIO_Module*)NULL,{(uint16_t)NULL,(GPIO_CurrentType)NULL,(GPIO_SpeedType)NULL,(GPIO_PuPdType)NULL,(GPIO_ModeType)NULL,(uint32_t)NULL)},
}


/**
  ******************************************************************************
  * @brief  led初始化 
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_led_init(void)
{
	uint8_t i;
	for(i = 0; i < (int)LEDMAX;i++)
	{
		GPIO_InitPeripheral(led_config[i].GPIOx,&led_config[i].GPIO_InitStructure);
	}
}


/**
  ******************************************************************************
  * @brief  led控制
  * @param  num：LED编号
  * @param  status：LED状态
  * @retval None.
  ******************************************************************************/