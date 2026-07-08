/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  lbm
  * @version V1.0
  * @date    2026-07-08
  * @brief   key驱动源文件
  ******************************************************************************
	*/

#include "bsp_key.h"

#define FILLTER_KEEP_TIME 10

key_param_t key_st_sp_param;
key_param_t key_cw_ccw_param;

//一个按键的所有成员属性
typedef struct
{
	key_enum_e num;
	GPIO_Module* GPIOx;
	GPIO_InitType InitStructure;
}gpio_config_t;


static gpio_config_t key_config[] = 
{
	START_STOP_KEY,GPIOC,{GPIO_PIN_6,GPIO_DC_2mA,GPIO_Slew_Rate_High,GPIO_Pull_Down,GPIO_Mode_Input,GPIO_NO_AF},
	CW_CCW_KEY,GPIOC,{GPIO_PIN_7,GPIO_DC_2mA,GPIO_Slew_Rate_High,GPIO_Pull_Down,GPIO_Mode_Input,GPIO_NO_AF},
	KEYMAX,(GPIO_Module*)NULL,{(uint16_t)NULL,(GPIO_CurrentType)NULL,(GPIO_SpeedType)NULL,(GPIO_PuPdType)NULL,(GPIO_ModeType)NULL,(uint32_t)NULL}
};

/**
  ******************************************************************************
  * @brief  bsp_key_rcc_config key的时钟设置
  * @param  None.
  * @retval None.
  ******************************************************************************/
static void bsp_key_rcc_config(void)
{
	KEY_CLK_CMD(KEY_GPIO_PORT,ENABLE);
}


/**
  ******************************************************************************
  * @brief  key初始化
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_key_init(void)
{
	bsp_key_rcc_config();
	uint8_t i = 0;
	for(i = 0 ; i < (int)KEYMAX; i++)
	{
		GPIO_InitPeripheral(key_config[i].GPIOx,&key_config[i].InitStructure);
	}
}


/**
  ******************************************************************************
  * @brief  按键扫描
  * @param  None.
  * @retval None.
  ******************************************************************************/
void bsp_key_scan(void)
{
	uint8_t key_val = 0;	//初始化键值
	key_val = GPIO_ReadInputDataBit(key_config[(int)START_STOP_KEY].GPIOx,key_config[(int)START_STOP_KEY].InitStructure.Pin);
	//printf("key_val = %d\r\n",key_val);
	/*第1步：start/stop按键检测，判断是否按下*/
	if(key_val == KEY_DOWN_VALUE && key_st_sp_param.triggle == 0)
	{
		key_st_sp_param.triggle = 0x01;
		key_st_sp_param.time = bsp_systick_time_get();
	}
	/*第2步：进行按键软件消抖滤波*/
	if(key_st_sp_param.triggle == 0x01)
	{
		//printf("test11\r\n");		//信息打印
		if(bsp_systick_time_get() - key_st_sp_param.time > FILLTER_KEEP_TIME)
		{
			/*10ms时间到：再次读取按键值是否是按下状态*/
			key_val = GPIO_ReadInputDataBit(key_config[(int)START_STOP_KEY].GPIOx,key_config[(int)START_STOP_KEY].InitStructure.Pin);
			if(key_val == KEY_DOWN_VALUE)
			{
				key_st_sp_param.down_sign = 1;	//按下状态：将按键按下标记设置为1
				key_st_sp_param.key_down_cnt++;
				printf("START/STOP KEY-->DOWN\r\n");		//信息打印
			}
			key_st_sp_param.triggle = 0x02;
		}
	}
	
	
	/*第3步：按键是抬起状态：将触发器值更新为0，为下一次按键动作做准备*/
	
	if(key_val == KEY_UP_VALUE && key_st_sp_param.triggle == 0x02)
	{
		printf("START/STOP KEY-->UP\r\n");		//信息打印
		key_st_sp_param.triggle = 0x00;		
		key_st_sp_param.down_sign = 0;
	}
	

	
	/****************************CC_CCW 按键*******************************************/
	key_val = GPIO_ReadInputDataBit(key_config[(int)CW_CCW_KEY].GPIOx, key_config[(int)CW_CCW_KEY].InitStructure.Pin);
	if(key_val == KEY_DOWN_VALUE && key_cw_ccw_param.triggle == 0x00)
	{
		key_cw_ccw_param.triggle = 0x01;
		key_cw_ccw_param.time = bsp_systick_time_get();
	}
	
	if(key_cw_ccw_param.triggle == 0x01)
	{
		if(bsp_systick_time_get() - key_cw_ccw_param.time > FILLTER_KEEP_TIME)
		{
			key_val = GPIO_ReadInputDataBit(key_config[(int)CW_CCW_KEY].GPIOx,key_config[(int)CW_CCW_KEY].InitStructure.Pin);
			if(key_val == KEY_DOWN_VALUE)
			{
				key_cw_ccw_param.down_sign = 0;			//抬起标志
				printf("CC/CCW KEY-->DOWN\r\n");		//信息打印
			}
			key_cw_ccw_param.triggle = 0x02;
		}
	}
	
	
	if(key_val == KEY_UP_VALUE && key_cw_ccw_param.triggle == 0x02)
	{
		//按键抬起
		printf("CC/CCW KEY-->UP\r\n");		//信息打印
		key_cw_ccw_param.down_sign = 1;	//为下一次按按键做准备
		key_cw_ccw_param.triggle = 0;
	}
}


