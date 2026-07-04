/**
  ******************************************************************************
  * @file    bsp_uart.h
  * @author  lbm
  * @version V1.0
  * @date    2026-07-03
  * @brief   uart驱动头文件
  ******************************************************************************
*/

#ifndef __BSP_UART_H__
#define __BSP_UART_H__


#include "n32g43x.h"

/************************************************************************/
#define DEBUG_UART	UART4
#define DEBUG_UART_CLK	RCC_APB2_PERIPH_UART4

#define DEBUG_UART_TX_GPIO				GPIOB
#define DEBUG_UART_TX_PIN					GPIO_PIN_0
#define DEBUG_UART_TX_GPIO_CLK		RCC_APB2_PERIPH_GPIOB
#define DEBUG_UART_TX_GPIO_AF			GPIO_AF6_UART4				//端口复用

#define DEBUG_UART_RX_GPIO				GPIOB
#define DEBUG_UART_RX_PIN					GPIO_PIN_1
#define DEBUG_UART_RX_GPIO_CLK		RCC_APB2_PERIPH_GPIOB
#define DEBUG_UART_RX_GPIO_AF			GPIO_AF6_UART4				//端口复用


#define DEBUG_UART_TX_GPIO_CLK_CMD	RCC_EnableAPB2PeriphClk
#define DEBUG_UART_RX_GPIO_CLK_CMD	RCC_EnableAPB2PeriphClk
#define	DEBUG_UART_CLK_CMD					RCC_EnableAPB2PeriphClk

#define	DEBUG_UART_IRQ							UART4_IRQn			//此编号在n32g43x.h的枚举体可以找到				
/************************************************************************/


typedef enum
{
    DEBUG_COM = 0,  //仿真调试接口

}uart_com_e;


typedef struct
{
	void (*debug_com_cb)(void);
}com_irq_cb_t;

extern com_irq_cb_t com_irq_cb;


//函数声明
void bsp_uart_init(uart_com_e com,uint32_t baud,void (*irq_cb)(void));
void bsp_uart_send_data(uart_com_e com,uint8_t *data,uint16_t len);
#endif
