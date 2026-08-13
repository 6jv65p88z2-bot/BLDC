/**
  ******************************************************************************
  * @file    bsp_adc.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-28
  * @brief   adc驱动源文件
  ******************************************************************************
*/


#include "bsp_adc.h"


//函数声明
static void bsp_adc_rcc_config(void);
static void bsp_adc_gpio_config(void);
static void bsp_adc_config(void);

adc_irq_cb_t adc_irq_cb = {NULL, NULL};


volatile uint16_t ADC_RegularConvertedValueTab[3];		//规则组缓冲区
volatile uint16_t ADC_InjectConvertedValueTab[4];		//注入组缓冲区


/**
  ******************************************************************************
  * @brief  adc时钟配置
  * @retval None.
  ******************************************************************************/
static void bsp_adc_rcc_config(void)
{
	RCC_EnableAHBPeriphClk(PERIPH_ADC_CLK,ENABLE);	//使能ADC外设时钟
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | PERIPH_GPIOA_CLK | PERIPH_GPIOC_CLK,ENABLE);		//使能GPIOA GPIOC端口时钟 工作时钟源     108MHZ
}	


/**
  ******************************************************************************
  * @brief  adc gpio配置
  * @retval None.
  ******************************************************************************/
static void bsp_adc_gpio_config(void)
{
	GPIO_InitType GPIO_InitStructure = {0};
	GPIO_InitStruct(&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
	GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
	
#if 1
		//这一种写法为了和源工程保持一致
		GPIO_InitStructure.Pin = GPIO_PIN_0;	//BEMF_U		ADC_IN1		PA0
		GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
		
		GPIO_InitStructure.Pin = GPIO_PIN_1;	//BEMF_V		ADC_IN2		PA1
		GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
			
		GPIO_InitStructure.Pin = GPIO_PIN_5;	//BEMF_V		ADC_IN6		PA1
		GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
			
		GPIO_InitStructure.Pin = GPIO_PIN_6;	//V_BUS			ADC_IN7		PA6		总线电压
		GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
			
		GPIO_InitStructure.Pin = GPIO_PIN_0;	//Temperature	ADC_IN11	PC0		温度
		GPIO_InitPeripheral(GPIOC,&GPIO_InitStructure);
			
		GPIO_InitStructure.Pin = GPIO_PIN_4;	//Speed			ADC_IN15	PC4		速度
		GPIO_InitPeripheral(GPIOC,&GPIO_InitStructure);
	
#else 
	//我觉得这样子的写法更为简洁
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5 |GPIO_PIN_6;
	GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_4;
	GPIO_InitPeripheral(GPIOC,&GPIO_InitStructure);

#endif
	
}
  
  /**
  ******************************************************************************
  * @brief  adc 配置
  * @retval None.
  ******************************************************************************/
static void bsp_adc_config(void)
{
	//ADC结构体
	ADC_InitType ADC_InitStructure;
	NVIC_InitType NVIC_InitStructure;
	
	//配置ADC规则通道：对齐模式、单次/连续转换、单通道/多通道
	ADC_InitStructure.ChsNumber = 3;		//规则通道的通道数为3个
	
	ADC_InitStructure.DatAlign = ADC_DAT_ALIGN_R;					//数据为右对齐的方式
	ADC_InitStructure.ExtTrigSelect = ADC_EXT_TRIGCONV_NONE;		//规则通道外部触发源选择：不使用外部触发源触发规则通道的转换
	ADC_InitStructure.ContinueConvEn = DISABLE;	//指定转换是是单次转换还是连续转换，disable为单次转换
	ADC_InitStructure.MultiChEn = ENABLE;		//指定转换是单通道和多通道选择，enable为选择多通道
	ADC_Init(ADC, &ADC_InitStructure);			//对ADC进行注册
	
	//设置规则通道：即规则通道应该采集哪些信息
	ADC_ConfigRegularChannel(ADC,ADC_CH_7,1,ADC_SAMP_TIME_13CYCLES5);	//该通道采集总线电压
	ADC_ConfigRegularChannel(ADC,ADC_CH_11,2,ADC_SAMP_TIME_13CYCLES5);	//该通道采集温度
	ADC_ConfigRegularChannel(ADC,ADC_CH_15,3,ADC_SAMP_TIME_13CYCLES5);	//该通道采集速度
	
	//设置注入通道：即注入通道应该采集哪些信息
	ADC_ConfigInjectedSequencerLength(ADC, 4);	//设置注入通道配置序列器长度
	
	ADC_ConfigInjectedChannel(ADC,ADC_CH_1,1,ADC_SAMP_TIME_13CYCLES5);	//该通道采集U相反电动势 BEMF_U
	ADC_ConfigInjectedChannel(ADC,ADC_CH_2,2,ADC_SAMP_TIME_13CYCLES5);	//该通道采集V相反电动势 BEMF_V
	ADC_ConfigInjectedChannel(ADC,ADC_CH_6,3,ADC_SAMP_TIME_13CYCLES5);	//该通道采集W相反电动势 BEMF_W
	
	//设置ADC注入通道外部触发
	ADC_ConfigExternalTrigInjectedConv(ADC,ADC_EXT_TRIG_INJ_CONV_T1_CC4);
	
	 /* 
		自动注入：通过启动规则通道转换后，注入通道开始自动启动转换
		触发注入：通过触发源也就是T1_CC4触发注入通道转换
	*/
	//选择ADC自动注入
	ADC_EnableAutoInjectedConv(ADC,DISABLE);	//所以这里要选择DISABLE，只要规则通道开启了，那么注入通道的 自动注入就会自动开启
	
	//启动ADC
	ADC_Enable(ADC,ENABLE);
	//等待ADC启动完成
	while(ADC_GetFlagStatusNew(ADC,ADC_FLAG_RDY) == RESET);
	
	//ADC校准
	ADC_StartCalibration(ADC);
	//等待ADC校准完成
	while(ADC_GetCalibrationStatus(ADC));
	//设置ADC的中断管理NVIC
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//最高的优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);		//对NVIC进行注册
	
	//使能注入通道转换完成的中断
	ADC_ConfigInt(ADC, ADC_INT_JENDC, ENABLE);		
	
	//开启ADC和DMA的关联
	ADC_EnableDMA(ADC,ENABLE);
	//开启ADC的外部触发模式
	ADC_EnableExternalTrigConv(ADC,ENABLE);
	//开启ADC的注入通道外部触发模式
	ADC_EnableExternalTrigInjectedConv(ADC,ENABLE);
	
	//首次软件触发一次规则通道转换，之后由中断回调自续触发
	ADC_EnableSoftwareStartConv(ADC, ENABLE);
}
  

/**
  ******************************************************************************
  * @brief  adc的dma配置
  * @retval None.
  ******************************************************************************/
static void bsp_adc_dma_config(void)
{
	DMA_InitType DMA_InitStructure;
	DMA_DeInit(DMA_CH1);
	
	//配置ADC的规则通道
	
	DMA_InitStructure.Mem2Mem = DMA_M2M_DISABLE;
	DMA_InitStructure.MemAddr = (uint32_t)&ADC_RegularConvertedValueTab;		//DMA内存地址
	DMA_InitStructure.MemDataSize = DMA_MemoryDataSize_HalfWord;				//内存数据长度为半字：2字节			
	DMA_InitStructure.DMA_MemoryInc = ENABLE;									//内存地址递增模式开启
	
	DMA_InitStructure.PeriphAddr = (uint32_t)&ADC->DAT;							//DMA外设地址
	DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;			//外设数据长度为半字：2字节
	DMA_InitStructure.PeriphInc = DISABLE;										//外设地址递增模式禁止
	DMA_InitStructure.BufSize = 3;												//目的缓冲区元素数，也就是内存缓冲区元素数
	DMA_InitStructure.CircularMode = DMA_MODE_CIRCULAR;							//DMA模式为循环模式
	DMA_InitStructure.Direction = DMA_DIR_PERIPH_SRC;							//DMA传输方向为外设到内存
	
	DMA_InitStructure.Priority = DMA_PRIORITY_HIGH;								//DMA优先级设置为高
	
	
	DMA_Init(DMA_CH1,&DMA_InitStructure);
	/*DMA重映射请求：将DMA CH1通道映射到ADC1*/
	DMA_RequestRemap(DMA_REMAP_ADC1,DMA,DMA_CH1,ENABLE);
	DMA_EnableChannel(DMA_CH1,ENABLE);
	
	
	
}

  
/**
  ******************************************************************************
  * @brief  adc初始化
  * @retval None.
  ******************************************************************************/
void bsp_adc_init(void)
{
	bsp_adc_rcc_config();
	bsp_adc_gpio_config();
	bsp_adc_config();
	bsp_adc_dma_config();
}

