#include "main.h"

uint8_t mpu_temp=2;//MPU��ʼ����־λ

void BSP_Init(void)						//�ײ��ʼ��
{
	//��ʼ��
	temperature_ADC_init();
	while(!get_set_temp());
//	while (ist8310_init() != IST8310_NO_ERROR);
	Read_Offset();
	while(mpu_temp) mpu_temp = mpu6500_init();//MPU��ʼ��	
	buzzer_init(30000, 90);
	led_configuration();
	led_io_cinfiguration();
//	while (ist8310_init() != IST8310_NO_ERROR);
	All_Pid_Configuration(pid);//pid������ʼ��
    power_ctrl_configuration();//24������ƿ� ��ʼ��
	TIM6_Configure();	
	TIM1_FireMotor_Configure();
	
	 //24v ��� �����ϵ�
    for (uint8_t i = POWER1_CTRL_SWITCH; i < POWER4_CTRL_SWITCH + 1; i++)
    {
        power_ctrl_on(i);
        delay_us(POWER_CTRL_ONE_BY_ONE_TIME);
    }
	
	//���ж�	
	Remote_uart1_init();//ң�س�ʼ��
	IMU_Configure();//MPU�жϳ�ʼ��
	TIM6_Start();
}
