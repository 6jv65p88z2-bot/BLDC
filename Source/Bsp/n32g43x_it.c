/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g43x_it.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32g43x_it.h"
#include "bsp_uart_cb.h"
#include "bsp_pwm_cb.h"

/** @addtogroup N32G43X_StdPeriph_Template
 * @{
 */

extern volatile uint32_t systick_count;

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles SVCall exception.
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 */
void SysTick_Handler(void)
{
    systick_count++;
}

/**
 * @brief  This function handles CAN RX0 Handler.
 */
void CAN_RX0_IRQHandler(void)
{
    
}


/******************************************************************************/
/*                 N32G43X Peripherals Interrupt Handlers                     */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_n32g43x.s).                                                 */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 */
/*void PPP_IRQHandler(void)
{
}*/


/**
 * @brief  This function handles USART3 global interrupt request.
 */
void USART3_IRQHandler(void)
{
    com_irq_cb.rs485_com_cb ();
}

/**
 * @brief  This function handles UART4 global interrupt request.
 */
void UART4_IRQHandler(void)
{
	com_irq_cb.debug_com_cb();
}

/**
 * @brief  This function handles UART5 global interrupt request.
 */
void UART5_IRQHandler(void)
{
	com_irq_cb.host_compute_com_cb();
}

/**
 * @brief  This function handles ADC global interrupt request.
 */
void ADC_IRQHandler(void)
{
	
}
uint32_t BRK_CNT = 0;
/**
 * @brief  This function handles tim1 brk global interrupt request.
 */
void TIM1_BRK_IRQHandler(void)
{
    
}

/**
 * @brief  This function handles tim1 update global interrupt request.
 */
void TIM1_UP_IRQHandler(void)
{
	pwm_irq_cb.pwm_cb();
}

/**
 * @brief  This function handles tim8 update global interrupt request.
 */
void TIM8_UP_IRQHandler(void)
{
	
}

/**
 * @brief  External lines 1 interrupt.
 */
void EXTI1_IRQHandler(void)
{
    
}

/**
 * @brief  External lines 2 interrupt.
 */
void EXTI2_IRQHandler(void)
{
    
}

/**
 * @brief  External lines 3 interrupt.
 */
void EXTI3_IRQHandler(void)
{
    
}

/**
 * @}
 */
