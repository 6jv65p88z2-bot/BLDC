#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "n32g43x.h"


typedef enum
{
    LED1 = 0,       //错误灯
    LED2,           //状态灯1
    LEN3,           //状态灯2
    LEDMAX
}led_num_e;

typedef struct
{
    led_num_e led_num;
    GPIO_Module *GPIOx;
    GPIO_InitType GPIO_InitStructuer;
}gpio_struct_t;



#endif

