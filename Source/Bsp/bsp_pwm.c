/**
  ******************************************************************************
  * @file    bsp_pwm.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-14
  * @brief   pwm驱动源文件
  ******************************************************************************
*/


#include "bsp_pwm.h"
#include <stdio.h>

#define MAIN_FREQUENCY	108000000		//主频Ft
#define PWM_FREQUENCY	20000			//载频Fpwm

pwm_irq_cb_t pwm_irq_cb = {NULL,NULL};

static uint16_t TimerPeriod = 0;



/**
  ******************************************************************************
  * @brief  pwm时钟初始化
  * @param  None
  * @retval None.
  ******************************************************************************/
static void bsp_pwm_rcc_config(void)
{
	//开启GPIO的时钟
	/*
	1.为什么开启GPIOA GPIOB的时钟：因为电机的三相六步中UH VH WH对应GPIOA，UL VL WL 对应GPIOB
	2.为什么开启AFIO复用时钟？因为需要通过GPIO的管脚来输出TIM1定时器的波形
	*/
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1,ENABLE);
}


/**
  ******************************************************************************
  * @brief  pwm的io timer1 该函数主要是利用GPIO管脚来输出三相高低电平的	
采用PWM控制三相电机的常用方法是：H_PWM-L_ON  上MOS使用PWM，下MOS常开
  * @param  None
  * @retval None.
  ******************************************************************************/
static void bsp_pwm_io_config(void)
{
	//在另外一个文件bsp_io.c中配置了PC5引脚 对time1进行测试
	
	GPIO_InitType GPIO_InitStructure = {0};
	// Configure TIM1, CH1(PA8),CH2(PA9),CH3(PA10),CH4(PA11) as alternate function push-pull
	GPIO_InitStruct(&GPIO_InitStructure);	//进行默认初始化
	
	GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_InitStructure.GPIO_Alternate= GPIO_AF2_TIM1;
	GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
	
#if 1
	// Configure TIM1, CH1N(PB13),CH2N(PB14),CH3N(PB15) as alternate function push-pull
    GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitPeripheral(GPIOB,&GPIO_InitStructure);
#else
	GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#endif	
}


/**
  ******************************************************************************
  * @brief  pwm的tiemr1的配置与基础测试
  * @param  None
  * @retval None.
  ******************************************************************************/

static void bsp_pwm_config(void)
{

	//可以理解为结构体句柄
	TIM_TimeBaseInitType TIM_TimBaseInitStructure;
	OCInitType TIM1_OCInitStructure;	//配置TIM1的输出比较器
	NVIC_InitType NVIC_InitStructure;

	#if 0
		/*
			1.目标：产生的定时器中断1ms1次
			2.系统主频：108MHZ
		3.因为1MHZ = 1000 000HZ,所以要想办法得到1MHZ，这样子根据周期和频率的公式，就可以得到具体的时间了。
		4.若想要中断2ms 1次，那么想办法得到2MHZ，那么PSC的值为：108 - 1，ARR的值为2000 - 1。
		5.同理，若想中断1us 1次，那么想办法得到定时器频率为1MHZ，PSC的值为108 - 1，ARR的值为1 - 1。
		*/
		TIM_InitTimBaseStruct(&TIM_TimBaseInitStructure);							//对TIM1进行默认初始化
		TIM_TimBaseInitStructure.ClkDiv = TIM_CLK_DIV1;								//时钟分频系数
		TIM_TimBaseInitStructure.CntMode = TIM_CNT_MODE_UP;							//计数模式
		TIM_TimBaseInitStructure.Period = 1000;										//计数周期（自动重装载值）		计数1000次就是1ms 
		//预分频写入值越大，counter计数器越慢；反之，预分频值越小，计数频率越高。
		TIM_TimBaseInitStructure.Prescaler = 108 - 1;  									//预分频值为108  1MHZ = 1000 000hz  T = 1/f = 1/1000000 = 0.000001s = 1us 也就是1us计数1次
		TIM_TimBaseInitStructure.RepetCnt = 0;										//重复计数
		
		TIM_InitTimeBase(TIM1,&TIM_TimBaseInitStructure);
		TIM_ConfigInt(TIM1,TIM_INT_UPDATE,ENABLE);									//设置定时器的中断，使能
		
		NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 16;					//抢占优先级(主)
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;							//响应优先级(子)
		
		NVIC_Init(&NVIC_InitStructure);
		//定时器1开启
		TIM_Enable(TIM1,ENABLE);													//使能TIM1
	
	#else
		TimerPeriod = MAIN_FREQUENCY / PWM_FREQUENCY  - 1;		//5399
		TIM_DeInit(TIM1);		//禁用TIM1
		TIM_InitTimBaseStruct(&TIM_TimBaseInitStructure);							//对TIM1进行默认初始化
		
		TIM_TimBaseInitStructure.Prescaler = 0;										//预分频为1，说明counter的计数频率非常快
		TIM_TimBaseInitStructure.CntMode = TIM_CNT_MODE_UP;
		TIM_TimBaseInitStructure.Period = TimerPeriod;								//5399
		TIM_TimBaseInitStructure.ClkDiv = TIM_CLK_DIV1;
		TIM_TimBaseInitStructure.RepetCnt = 0;
		
		TIM_InitTimeBase(TIM1,&TIM_TimBaseInitStructure);
		//Channel 1, 2,3 in PWM mode
		TIM_InitOcStruct(&TIM1_OCInitStructure);						//输出比较寄存器的默认初始化
		TIM1_OCInitStructure.OcMode = TIM_OCMODE_PWM1;					//输出比较寄存器选择PWM1 模式
		TIM1_OCInitStructure.OutputState= TIM_OUTPUT_STATE_ENABLE;		//CH1-CH3输出通道开启
		TIM1_OCInitStructure.OutputNState= TIM_OUTPUT_NSTATE_ENABLE;	//CH1N-CH3N输出通道开启  
		TIM1_OCInitStructure.Pulse = 2699;								//初始输出占空比都为0，Pulse值对应CCDATx寄存器
		
		/*	如果couter计数器计数值小于等于Pulse值，CH1-CH4通道输出高电平
			如果couter计数器计数值大于Pulse值，CH1-CH4通道输出低电平
		*/
		TIM1_OCInitStructure.OcPolarity = TIM_OC_POLARITY_HIGH;			//正常通道 输出高电平
		
		
		/*	如果couter计数器计数值小于等于Pulse值，CH1N-CH3N通道输出低电平
			如果couter计数器计数值大于Pulse值，CH1N-CH3N通道输出高电平
		*/
		TIM1_OCInitStructure.OcNPolarity = TIM_OCN_POLARITY_HIGH;		//镜像通道 输出低电平
		
		
		TIM1_OCInitStructure.OcIdleState = TIM_OC_IDLE_STATE_SET;	//初始状态或占空比值为0时CH1-CH4通道输出低电平
		TIM1_OCInitStructure.OcNIdleState= TIM_OCN_IDLE_STATE_SET;	//初始状态或占空比值为0时CH1N-CH3N通道输出低电平   
		TIM_InitOc1(TIM1,&TIM1_OCInitStructure);
		TIM_InitOc2(TIM1,&TIM1_OCInitStructure);
		TIM_InitOc3(TIM1,&TIM1_OCInitStructure);
		
		//Channel 4 Configuration in OC 
		
		TIM1_OCInitStructure.OcMode = TIM_OCMODE_PWM1;//Pos logic(when '<' is active(激活活动),when '>' is inactive(不活跃的，未激活的))
		TIM1_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;	//CH4输出通道开启
		TIM1_OCInitStructure.Pulse = 2699;							//初始输出占空比都为0，Pulse值对应CCDATx寄存器
		TIM_InitOc4(TIM1, &TIM1_OCInitStructure);
		
		//TIM1 counter enable
		TIM_Enable(TIM1, ENABLE);
		TIM_EnableCtrlPwmOutputs(TIM1,ENABLE);
	#endif



}


/**
  ******************************************************************************
  * @brief  pwm初始化 timer1
  * @param  irq_cb:timer 的中断回调指针
	@param  irq_bk_cb:timer brake中断回调指针
  * @retval None.
  ******************************************************************************/
//void bsp_pwm_init(void (*irq_bk_cb)(void),void (*irq_cb)(void))
void bsp_pwm_init(void (*irq_cb)(void))
{
	if(irq_cb == NULL)
	{
		while(1);//空指针，直接进入死循环
	}
	pwm_irq_cb.pwm_cb = irq_cb;		//若TIM1产生更新中断，则会把TIM1的回调函数在这里进行赋值
	//pwm_irq_cb.pwm_bk_cb = irq_bk_cb; //若TIM7产生更新中断，则会把TIM1的回调函数在这里进行赋值
	
	bsp_pwm_rcc_config();
	bsp_pwm_io_config();
	bsp_pwm_config();	
}
