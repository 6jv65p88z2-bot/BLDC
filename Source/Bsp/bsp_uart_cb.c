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


static uint8_t rs485_recv_buf[1024];
static uint32_t findex = 0;
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
	if(USART_GetIntStatus(HOST_COMPUTER_UART,USART_INT_RXDNE))
	{
		//如果UART的中断状态为“接收寄存器满”，则把收到的数据发送出去
		data = USART_ReceiveData(HOST_COMPUTER_UART);
		bsp_uart_send_data(HOST_COMPUTER_COM,&data,1);		//感觉这个1可能有问题 暂时未测试
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
	
	if(USART_GetIntStatus(RS485_UART,USART_INT_RXDNE) != RESET)
	{
		rs485_recv_buf[findex++] = USART_ReceiveData(RS485_UART);
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