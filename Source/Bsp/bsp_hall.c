/**
  ******************************************************************************
  * @file    bsp_hall.c
  * @author  lbm
  * @version V1.0
  * @date    2026-8-11
  * @brief   hall源文件
  ******************************************************************************/

#include "bsp_hall.h"
#include <stdio.h>

//函数声明
static void bsp_hall_rcc_config(void);
static void bsp_hall_gpio_config(void);

hall_irq_cb_t hall_irq_cb= {NULL};


/**
  ******************************************************************************
  * @brief  hall的时钟配置
  * @retval None.
  ******************************************************************************/
static void bsp_hall_rcc_config(void)
{
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC,ENABLE);
}

static void bsp_hall_gpio_config(void)
{
	GPIO_InitType GPIO_InitStructure = {0};
	// HALL:U PC1 	HALL:V PC2 	HALL:W PC3
	GPIO_InitStruct(&GPIO_InitStructure);		//使用默认初始化
	GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
	GPIO_InitStructure.GPIO_Pull = GPIO_No_Pull;
	GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitPeripheral(GPIOC,&GPIO_InitStructure);
}

/**
  ******************************************************************************
  * @brief  hall中断开启
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_hall_irq_enable(void)
{
	EXTI_InitType EXTI_InitStrucutre = {0};
	NVIC_InitType NVIC_InitStructure = {0};
	
	//配置外部中断
	EXTI_InitStrucutre.EXTI_Line = EXTI_LINE1;					//PC1 HALL_U
	EXTI_InitStrucutre.EXTI_Mode = EXTI_Mode_Interrupt;		//中断触发
	EXTI_InitStrucutre.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  //io产生上升沿/下降沿触发
	EXTI_InitStrucutre.EXTI_LineCmd = DISABLE;
	EXTI_InitPeripheral(&EXTI_InitStrucutre);
	
	EXTI_InitStrucutre.EXTI_Line = EXTI_LINE2;					//PC2 HALL_V
	EXTI_InitPeripheral(&EXTI_InitStrucutre);
	
	EXTI_InitStrucutre.EXTI_Line = EXTI_LINE3;					//PC3 HALL_W
	EXTI_InitPeripheral(&EXTI_InitStrucutre);
	
	//配置NVIC中断管理
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel                   = EXTI2_IRQn;
    NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel                   = EXTI3_IRQn;
    NVIC_Init(&NVIC_InitStructure);
	
}

/**
  ******************************************************************************
  * @brief  hall中断关闭
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_hall_irq_disable(void)
{
	EXTI_InitType EXTI_InitStrucutre = {0};
	NVIC_InitType NVIC_InitStructure = {0};
	
	//配置外部中断
	EXTI_InitStrucutre.EXTI_Line = EXTI_LINE1;
	EXTI_InitStrucutre.EXTI_Mode = EXTI_Mode_Interrupt;		//中断触发
	EXTI_InitStrucutre.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  //io产生上升沿/下降沿触发
	EXTI_InitStrucutre.EXTI_LineCmd = DISABLE;
	EXTI_InitPeripheral(&EXTI_InitStrucutre);
	
	EXTI_InitStrucutre.EXTI_Line = EXTI_LINE2;
	EXTI_InitPeripheral(&EXTI_InitStrucutre);
	
	EXTI_InitStrucutre.EXTI_Line = EXTI_LINE3;
	EXTI_InitPeripheral(&EXTI_InitStrucutre);
	
	//配置NVIC中断管理
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel                   = EXTI2_IRQn;
    NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel                   = EXTI3_IRQn;
    NVIC_Init(&NVIC_InitStructure);
	
}

/**
  ******************************************************************************
  * @brief  hall初始化
  * @param  irq_cb:中断回调指针数组
  * @param  formal_param:中断回调指针数组中形参
  * @retval None.
  ******************************************************************************/
//void bsp_hall_init(void( *irq_cb[3])(void (*formal_param)(void)),void (*formal_param)(void))
void bsp_hall_init(void( *irq_cb[3])(void (*formal_param)(void)))
{
	if((irq_cb[0] == NULL) || (irq_cb[1] == NULL) || (irq_cb[2] == NULL) )
	//if((irq_cb[0] == NULL) || (irq_cb[1] == NULL) || (irq_cb[2] == NULL) || (formal_param == NULL))
	{
		while(1);	//卡死在此处
	}
	//回调赋值
	hall_irq_cb.hall_u_cb = irq_cb[0];
	hall_irq_cb.hall_v_cb = irq_cb[1];
	hall_irq_cb.hall_w_cb = irq_cb[2];
	//hall_irq_cb.formal_param = formal_param;
	
	
	//1.开启时钟
	bsp_hall_rcc_config();
	//2.GPIO配置
	bsp_hall_gpio_config();
	//3.配置管脚输入的外部中断线
	GPIO_ConfigEXTILine(GPIOC_PORT_SOURCE, GPIO_PIN_SOURCE1);
	GPIO_ConfigEXTILine(GPIOC_PORT_SOURCE, GPIO_PIN_SOURCE2);
	GPIO_ConfigEXTILine(GPIOC_PORT_SOURCE, GPIO_PIN_SOURCE3);
	
	//4.初始化关闭中断
	bsp_hall_irq_disable();
}

