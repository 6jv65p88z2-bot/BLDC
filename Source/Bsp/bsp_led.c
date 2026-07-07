#include "bsp_led.h"

static gpio_struct_t led_config[] = 
{
	LED1,GPIOC,{GPIO_PIN_15,GPIO_DC_2mA,GPIO_Slew_Rate_High,GPIO_No_Pull,GPIO_Mode_Out_OD,GPIO_NO_AF},
	LED2,GPIOC,{GPIO_PIN_14,GPIO_DC_2mA,GPIO_Slew_Rate_High,GPIO_No_Pull,GPIO_Mode_Out_OD,GPIO_NO_AF},
	LED2,GPIOC,{GPIO_PIN_13,GPIO_DC_2mA,GPIO_Slew_Rate_High,GPIO_No_Pull,GPIO_Mode_Out_OD,GPIO_NO_AF},
	LEDMAX,(GPIO_Module*)NULL,{(uint16_t)NULL,(GPIO_CurrentType)NULL,(GPIO_SpeedType)NULL,(GPIO_PuPdType)NULL,(GPIO_ModeType)NULL,(uint32_t)NULL}
};


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
  * @brief  led电平翻转
	* @param  不知道触发电平翻转后，while(1)死循环会不会造成整一个程序卡死
  * @param  None.
  * @retval None.
  ******************************************************************************/
static void bsp_led_toggle(led_num_e num)
{
	while(1)
	{
		GPIO_SetBits(led_config[num].GPIOx,led_config[num].GPIO_InitStructure.Pin);
		bsp_delay_ms(500);
		GPIO_ResetBits(led_config[num].GPIOx,led_config[num].GPIO_InitStructure.Pin);
		bsp_delay_ms(500);
	}
}

/**
  ******************************************************************************
  * @brief  led控制
  * @param  num：LED编号
  * @param  status：LED状态
  * @retval None.
  ******************************************************************************/
void bsp_led_ctrl(led_num_e num,uint8_t status)
{
	uint8_t i;
	for(i = 0 ; i < (int)LEDMAX;i++)
	{
		if(status == LED_ON)
		{
			GPIO_SetBits(led_config[i].GPIOx,led_config[i].GPIO_InitStructure.Pin);
		}else if(status == LED_OFF)
		{
			GPIO_ResetBits(led_config[i].GPIOx,led_config[i].GPIO_InitStructure.Pin);
		}else if(status == LED_TOGGLE)
		{
			//电平翻转,500ms闪烁一次
			bsp_led_toggle(num);
		}
	}
}

