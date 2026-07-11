/**
  ******************************************************************************
  * @file    bsp_key.h
  * @author  lbm
  * @version V1.0
  * @date    2026-07-08
  * @brief   key驱动头文件
  ******************************************************************************
	*/

#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "n32g43x.h"
#include "bsp_systick.h"
#include <stdio.h>


//根据原理图，按下接3.3V为高电平，所以将按下键值置位为1
#define KEY_DOWN_VALUE 	0x01		//按键按下键值
#define KEY_UP_VALUE		0x00		//按键抬起键值

#define KEY_CLK_CMD		RCC_EnableAPB2PeriphClk
#define KEY_GPIO_PORT	RCC_APB2_PERIPH_GPIOC




//按键种类
typedef enum
{
	START_STOP_KEY = 0,
	CW_CCW_KEY ,
	KEYMAX
}key_enum_e;






//一个按键的所有参数
typedef struct
{
	uint32_t time;			//时间记录
	uint8_t triggle;		//触发标记
	uint8_t down_sign;	//按下标记
	uint32_t key_down_cnt;	//按键按下计数
	
}key_param_t;


extern key_param_t key_st_sp_param;
extern key_param_t key_cw_ccw_param;


//函数声明
void bsp_key_init(void);
void bsp_key_scan(void);




#endif

