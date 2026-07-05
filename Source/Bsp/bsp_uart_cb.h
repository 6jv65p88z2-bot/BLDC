/**
  ******************************************************************************
  * @file    bsp_uart_cb.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-03
  * @brief   uart回调头文件
  ******************************************************************************
*/


#ifndef __BSP_UART_CB_H__
#define __BSP_UART_CB_H__


#include "n32g43x.h"
#include "bsp_uart.h"

//函数声明
void bsp_debug_com_irq_cb(void);
 void bsp_host_computer_com_irq_cb(void);
#endif

