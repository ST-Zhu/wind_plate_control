#include "main.h"

uint8_t mpu_temp=2;//MPU初始化标志位

void BSP_Init(void)						//底层初始化
{
	//初始化
	temperature_ADC_init();
	while(!get_set_temp());
//	while (ist8310_init() != IST8310_NO_ERROR);
	Read_Offset();
	while(mpu_temp) mpu_temp = mpu6500_init();//MPU初始化	
	buzzer_init(30000, 90);
	led_configuration();
	led_io_cinfiguration();
//	while (ist8310_init() != IST8310_NO_ERROR);
	All_Pid_Configuration(pid);//pid参数初始化
    power_ctrl_configuration();//24输出控制口 初始化
	TIM6_Configure();	
	TIM1_FireMotor_Configure();
	
	 //24v 输出 依次上电
    for (uint8_t i = POWER1_CTRL_SWITCH; i < POWER4_CTRL_SWITCH + 1; i++)
    {
        power_ctrl_on(i);
        delay_us(POWER_CTRL_ONE_BY_ONE_TIME);
    }
	
	//开中断	
	Remote_uart1_init();//遥控初始化
	IMU_Configure();//MPU中断初始化
	TIM6_Start();
}
