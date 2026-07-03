/**
  ******************************************************************************
  * @file    bsp_uart.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-03
  * @brief   uart驱动源文件
  ******************************************************************************
*/

#include "bsp_uart.h"
#include <stdio.h>

com_irq_cb_t com_irq_cb = {NULL};

/**
  ******************************************************************************
  * @brief  UART关联RCC时钟配置
  * @param  com:端口号
  * @retval None.
  ******************************************************************************/
void bsp_uart_rcc_config(uart_com_e com)
{
    switch(com)
    {
        case DEBUG_COM:
					//开启UART TX RX的时钟
					DEBUG_UART_TX_GPIO_CLK_CMD(DEBUG_UART_TX_GPIO_CLK,ENABLE);
					DEBUG_UART_RX_GPIO_CLK_CMD(DEBUG_UART_RX_GPIO_CLK,ENABLE);
					DEBUG_UART_CLK_CMD(DEBUG_UART_CLK,ENABLE);
					break;
				
    }
}



/**
  ******************************************************************************
  * @brief  UART初始化
  * @param  com :端口号
  * @param  baud:设置波特率
  * @param  irq_cb:中断回调指针
  * @retval None.
  ******************************************************************************/
void bsp_uart_gpio_config(uart_com_e com,uint32_t baud)
{
	GPIO_InitType	GPIO_InitStructure = {0};
	GPIO_InitStruct(&GPIO_InitStructure);
	switch(com)
	{
		case DEBUG_COM:

		//配置TX引脚
			GPIO_InitStructure.GPIO_Alternate = DEBUG_UART_TX_GPIO_AF;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出	
			GPIO_InitStructure.Pin = DEBUG_UART_TX_PIN;
			GPIO_InitPeripheral(DEBUG_UART_TX_GPIO,&GPIO_InitStructure);

		//配置RX引脚
			GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Up;		//上拉模式
			GPIO_InitStructure.Pin = DEBUG_UART_RX_PIN;
			GPIO_InitStructure.GPIO_Alternate = DEBUG_UART_RX_GPIO_AF;
			break;
	}
	
	
}

/**
  ******************************************************************************
  * @brief  UART初始化
  * @param  com :端口号
  * @param  baud:设置波特率
  * @param  irq_cb:中断回调指针
  * @retval None.
  ******************************************************************************/
 void bsp_uart_init(uart_com_e com,uint32_t baud,void (*irq_cb)(void))
 {
    USART_InitType USART_InitStructure = {0};
    NVIC_InitType NVIC_InitStructure = {0};

    USART_StructInit(&USART_InitStructure);

    //配置串口时钟
    bsp_uart_rcc_config(com);
    //配置串口的GPIO引脚
		bsp_uart_gpio_config(com,baud);
		
		if(irq_cb == NULL)
		{
			//野指针
			while(1);
		}
		
		
		//根据端口号来配置不同的串口
		switch(com)
		{
			case DEBUG_COM:
				//配置串口
			USART_InitStructure.BaudRate = baud;
			USART_InitStructure.WordLength = USART_WL_8B;
			USART_InitStructure.StopBits = USART_STPB_1;
			USART_InitStructure.Parity = USART_PE_NO;
			USART_InitStructure.Mode = USART_MODE_RX | USART_MODE_TX;
			USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
				//配置串口和NVIC中断控制器的关系
			NVIC_InitStructure.NVIC_IRQChannel = DEBUG_UART_IRQ;		//UART的中断编号
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			
				//设置DEBUG_UART和NVIC关联起来
			USART_ConfigInt(DEBUG_UART,USART_INT_RXDNE,ENABLE);	//接收寄存器满，产生中断
			com_irq_cb.debug_com_cb = irq_cb;	//回调赋值
				//调用api接口初始化串口
			USART_Init(DEBUG_UART,&USART_InitStructure);
				//开启串口
			USART_Enable(DEBUG_UART,ENABLE);		
			break;
		}	
 }
 
 
 /**
  ******************************************************************************
  * @brief  UART阻塞方式发送不定长数据,实际上可以类比江科大的Serial_SendAray函数
  * @param  com :端口号
  * @param  data:发送数据指针
  * @param  len :发送数据长度
  * @retval None.
  ******************************************************************************/
 void bsp_uart_send_data(uart_com_e com,uint8_t *data,uint16_t len)
 {
	int i = 0;
	USART_Module *uart = NULL;
	switch(com)
	{
		case DEBUG_COM:
			uart = DEBUG_UART;
			break;
	}

	if(uart == NULL)
	{
		while(1);	//野指针
	}

	//开始发送数组里面的数据
	//还可以对下面这个for循环进行封装
	for(i = 0; i < len ;i++)
	{
		//发送数据
		USART_SendData(uart,data[i]);
		while(USART_GetFlagStatus(uart,USART_FLAG_TXDE) == RESET);	//等待发送完成
	}

	switch(com)
	{
		case DEBUG_COM;
			break;
	}
 }

 
 