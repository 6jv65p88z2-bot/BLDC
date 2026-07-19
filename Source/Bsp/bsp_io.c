/**
  ******************************************************************************
  * @file    bsp_io.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-19
  * @brief   ioÇý¶¯
  ******************************************************************************
*/
  
  
  
 
#include "bsp_io.h"


/**
  ******************************************************************************
  * @brief  io³õÊ¼»¯
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_io_init(void)
{
	GPIO_InitType GPIO_InitStructure;
	// Enable GPIO clocks 
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD, ENABLE);
	
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.Pin       = GPIO_PIN_5;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
#if 0	
	GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.Pin       = GPIO_PIN_12;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#endif	
}