#include "main.h"

extern u8 offset_OK_flag;
extern u8 offset_OK_flag1;
extern u8 run_flag;

void control_task() 
{
	if(run_flag == 1)//����
	{
		if(offset_OK_flag1 == 1)
		{
			//�����㷨	
			fireMotor_control();//Ħ���ֿ���		
		}
	}
	else if(run_flag == 2)//У׼
	{
		if(offset_OK_flag == 2)
		{
			cali_gyro_hook();
		}
		else if(offset_OK_flag == 1)
		{
			run_flag = 1;
		}
	}
}

