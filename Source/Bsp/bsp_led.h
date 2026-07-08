#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "n32g43x.h"
#include <stdio.h>
#include "bsp_systick.h"

#define LED_ON 0	//亮
#define LED_OFF 1	//灭
#define LED_TOGGLE	2	//电平翻转

typedef enum
{
    LED1 = 0,       //错误灯
    LED2,           //状态灯1
    LED3,           //状态灯2
    LEDMAX
}led_num_e;

typedef struct
{
    led_num_e led_num;
    GPIO_Module *GPIOx;
    GPIO_InitType GPIO_InitStructure;
}gpio_config_t;


//函数声明
void bsp_led_init(void);
void bsp_led_ctrl(led_num_e num,uint8_t status);



#endif

