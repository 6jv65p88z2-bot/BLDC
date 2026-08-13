2026.7.4日软件更新日志
(1) UART测试成功，bsp_uart_send_data,printf;均测试成功。

2026.7.5日软件更新日志
(1) HOST_COMPUTER_COM 和 RS485_COM的代码全部写完了，但是还没有测试过。
(2) 除了出厂的检查代码没有写。
(3) 已经上传到github上面备份v1.3_4。

2026.7.6日软件更新日志
（1）调通了HOST_COMPUTER_COM，但是 RS485_COM尚未调通，还需要一个USB转485的转换器。

2026.7.7日软件更新日志
（1）撰写完成bsp_led.c文件，添加了LED电平翻转功能，但是还没有测试。

2026.7.8日软件更新日志
（1）调通LED，并且LED电平翻转功能也正常。
（2）systick滴答计数器正常计数。v1.3_7
（3）调通了KEY按键，并且完成了测试，封装好了时钟函数。v1.3_8

2026.7.10日软件更新日志
(1)完成bsp_opa1.c的代码，但是未测试。
(2)测试完成bsp_opa1.c和bsp_dac.c文件，测试符合预期。

2026.7.13日软件更新日志
(1).创建4个文件：bsp_timer.c和bsp_timer.h、bsp_pwm.c和bsp_pwm.h。
(2).pwm使用高级定时器1触发脉冲方波，timer.c是timer8的高级定时器设置。


2026.7.14日软件更新日志
(1)完成了TIM1的代码撰写，包括文件bsp_pwm.c bsp_pwm.h bsp_pwm_cb.c  bsp_pwm_cb.h
(2)目前没有语法错误,当前版本:v1.4.2
(3)TIM1还没有进行测试，测试方法：使用逻辑分析仪，把探针接在PC5引脚上，观察输出的高低电平，PWM波是否周期是1ms

2026.7.19日软件更新日志
(1)完成了TIM1的代码测试，1ms产生一次中断，使用逻辑分析仪抓取数据，验证高电平1ms，低电平1ms，周期2ms，占空比50%。
(2)逻辑分析仪接线方式：逻辑分析仪和开发板共GND，逻辑分析仪的CH1接开发板的PC5。
(3)尝试使用500ms的方式来抓波形，成功。比1ms的方波要更加密集一些。
(4)TIM1的三相代码已经完成，有关于刹车信号的PWM暂时还没有撰写。测试结果逻辑分析仪第7通道可以采集到波形，但是前面的6个通道采集不到。
	推测原因：
	1）只有可能是硬件层面上接线有问题。22:47 已经解决此问题，原因：接线接错位置了。
	(5)目前github上是v1.4.3版本，已经完成了UVW三相的波形抓取，占空比为50%。还剩下3个函数bsp_pwm_duty_set、bsp_all_pwm_open、bsp_all_pwm_close未撰写未测试。


2026.7.26日软件更新日志
(1)完成3个函数bsp_pwm_duty_set、bsp_all_pwm_open、bsp_all_pwm_close，但是未测试。
(2)github->v1.4.4。

2026.7.27日软件更新日志
(1)完成TIM1的刹车引脚配置和刹车功能软件配置实现，语法层面上没有错误。【已完成未测试】
(2)测试方法：
	①先完成adc的电流采集。【未完成】
	②copy源码的出厂检测函数，打开串口，输入指令overflow后，强制刹停电机。【未完成】
	【说明】我觉得这里可以不用接电机那么快，因为电机的代码还没有写。可以利用命令overflow来测试该功能是否OK。直接通过串口打印电流值，
			输入命令overflow后能够使得采集的电流为0.0A，说明刹车功能触发了。这样子的测试就OK了。
			原理：直接设置dac的值为0，使得运放opa1 强制大于 dac，使得输出高电平，从而触发了刹车。
(3)github->v1.4.5。

2026.7.28日软件更新日志
(1)完成bsp_adc.c模块中的函数bsp_adc_rcc_config、bsp_adc_gpio_config。

2026.7.29日软件更新日志
(1)完成bsp_adc.c模块中的函数bsp_adc_config，同时在这个函数中开启了ADC和DMA的关联。但是还没有配置DMA。

2026.7.31日软件更新日志
（1）完成bsp_adc_dma_config(void)函数。
（2）github->1.4.7

2026.8.1日软件更新日志
(1) 完成bsp_adc_irq_cb(void) ADC回调函数。github->1.4.8
(2)ADC的ISR程序ADC_Handler里面我还没有写任何函数，也就是目前ADC没有进行主函数初始化以及回调函数的调用。
(3) ADC测试方法：
*********************************************************************
*********************************************************************
// 在 while(1) 中添加（在 bsp_key_scan() 之前或之后）：
// ADC 测试：每1秒打印一次 ADC 采集数据
static uint32_t adc_test_tick = 0;
if (bsp_systick_time_get() - adc_test_tick >= 1000)  // 每1000ms
{
    adc_test_tick = bsp_systick_time_get();
    
    printf("=== ADC Data ===\r\n");
    printf("V_Bus:       %d\r\n", adc_digital_val.v_bus);
    printf("Temperature: %d\r\n", adc_digital_val.temperature);
    printf("Speed:       %d\r\n", adc_digital_val.speed);
    printf("Current:     %d\r\n", adc_digital_val.current);
    printf("BEMF_U:      %d\r\n", adc_digital_val.bemf_u);
    printf("BEMF_V:      %d\r\n", adc_digital_val.bemf_v);
    printf("BEMF_W:      %d\r\n", adc_digital_val.bemf_w);
    printf("ttt_cnt:     %d\r\n\r\n", ttt_cnt);  // 中断计数，验证注入触发频率
}
*********************************************************************
*********************************************************************

2026.8.5日软件更新日志
(1)凌晨36分，调试了一下PWM的代码，发现：很多错误和Bug,都源自于自己不小心的一些细节问题。
(2)我建议还是要写完一个模块，就要立马去测试，不然后面测试起来很麻烦。
(3)目前github->1.4.8，硬件层面没问题，打开刹车信号代码，以及其他的PWM7路都可以顺利抓出波形，也可以随便改变duty值。
但是在while(1)循环里面，没有办法在watch窗口中更改值，我记得视频中是可以修改的。

2026.8.6日软件更新日志
(1)bsp_pwm_duty_set、bsp_all_pwm_open、bsp_all_pwm_close 全部测试正常，逻辑分析仪验证正确。

2026.8.11日软件更新日志
(1)更新了bldc_motor工程的分层架构，把所有的回调函数，全部单独放在一个文件夹Bsp_cb。语法检查通过。
(2)github->1.4.9
(3)bsp_hall.c文件已经写了一点代码。

2026.8.12日软件更新日志
(1)github->1.5.1    之前1.4.9无法同步到github上面，所以这里改为1.5.1，现在可以同步上去了
(2)完成bsp_hall_init(hall_uvw_irq_cb)，但是未完成：bsp_hall_init(hall_uvw_irq_cb, motor_sensor_mode_phase);我觉得后面的形参2应该是要学习了霍尔传感器的知识后才去撰写的代码。
(3)githhub->1.5.2 已经更新。

2026.8.13日软件更新日志
一、计划
(1)完成母线电压值和温度值计算的代码撰写		
(2)完成hall接口驱动层采集传感数据的代码撰写
二、总结
(1) 已经完成了母线电压值的采集。剩下的未完成。
(2)github->v1.5.3。
