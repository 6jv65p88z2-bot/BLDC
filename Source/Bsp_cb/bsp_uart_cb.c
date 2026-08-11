/**
  ******************************************************************************
  * @file    bsp_uart_cb.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-03
  * @brief   uart回调源文件
  ******************************************************************************
	
*/

#include "bsp_uart_cb.h"
#include "bsp_uart.h"
#include <string.h>		//为了使用函数strncmp导入

static uint8_t rs485_recv_buf[1024];
static uint32_t findex = 0;

factory_func_check_t factory_func_check;

/**
  ******************************************************************************
  * @brief  出厂参数命令检测
  * @param  data:接收串口数据
  * @retval None.
  ******************************************************************************/
static void bsp_factory_cmd_analyse(uint8_t data)
{
	static uint8_t len = 0;
	static uint8_t recv_buf[32] = {0};	//接收数据的缓冲区
	
	recv_buf[len++] = data;
	
	if(recv_buf[len - 1] == '\n')
	{
		/*OVERFLOW过流功能测试*/
		if(strncmp((char *)recv_buf,"OVERFLOW",8) == 0)
		{
			//说明在缓冲区recv_buf中找到了OVERFLOW
			factory_func_check.overflow_sign = 0xFF;
		}
	}
}
  
/**
  ******************************************************************************
  * @brief  debug com中断回调
  * @param  com:端口号
  * @retval None.
  ******************************************************************************/

void bsp_debug_com_irq_cb(void)
{
	uint8_t data = 0;
	if (USART_GetIntStatus(DEBUG_UART, USART_INT_RXDNE) != RESET)
	{
		//如果UART的中断状态为“接收寄存器满”，则把收到的数据发送出去
		data = USART_ReceiveData(DEBUG_UART);
		bsp_factory_cmd_analyse(data);		//出厂数据分析
		bsp_uart_send_data(DEBUG_COM,&data,1);
	}
	
	if(USART_GetIntStatus(DEBUG_UART,USART_INT_TXDE) != RESET)
	{
		//USART_SendData(DEBUG_UART,data);
	}
	
	if(USART_GetIntStatus(DEBUG_UART,USART_INT_OREF) != RESET)
	{
		//如果产生了错误，则清标志位
		(void)DEBUG_UART->STS;
		(void)DEBUG_UART->DAT;
	}
}

/**
  ******************************************************************************
  * @brief  host_compute_com_cb com中断回调
  * @param  com:端口号
  * @retval None.
  ******************************************************************************/
 void bsp_host_computer_com_irq_cb(void)
 {
	uint8_t data = 0;
	if(USART_GetIntStatus(HOST_COMPUTER_UART,USART_INT_RXDNE) != RESET)
	{
		//如果UART的中断状态为“接收寄存器满”，则把收到的数据发送出去
		//所以就会看到如下：
		data = USART_ReceiveData(HOST_COMPUTER_UART);
		bsp_uart_send_data(HOST_COMPUTER_COM,&data,1);		
	}

	if(USART_GetIntStatus(HOST_COMPUTER_UART,USART_INT_TXDE) != RESET)
	{
		//USART_SendData(HOST_COMPUTER_UART,data);
	}

	if(USART_GetIntStatus(HOST_COMPUTER_UART,USART_INT_OREF) != RESET)
	{
		//如果产生了错误，则清标志位
		(void)HOST_COMPUTER_UART->STS;
		(void)HOST_COMPUTER_UART->DAT;
	}
 }

 /**
  ******************************************************************************
  * @brief  rs485 com中断回调
  * @param  com:端口号
  * @retval None.
  ******************************************************************************/
 void bsp_rs485_com_irq_cb(void)
 {
	uint8_t data = 0;
	if(USART_GetIntStatus(RS485_UART,USART_INT_RXDNE) != RESET)
	{
		data =  USART_ReceiveData(RS485_UART);
		rs485_recv_buf[findex++] = data;
		bsp_uart_send_data(RS485_COM, &data, 1);
		
		if(findex >= sizeof(rs485_recv_buf))
		{
			findex = 0;
		}
	}

	if(USART_GetIntStatus(RS485_UART,USART_INT_TXDE) != RESET)
	{
		//USART_SendData(RS485_UART,data);
	}

	if(USART_GetIntStatus(RS485_UART,USART_INT_OREF) != RESET)
	{
		//如果产生了错误，则清标志位
		(void)RS485_UART->STS;
		(void)RS485_UART->DAT;
	}
}

