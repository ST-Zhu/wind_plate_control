#include "main.h"

Board_Control board_control = {0};
Fire_Motor fire_motor = {0};
Fire_Enconder fire_enconderL = {0};
Fire_Enconder fire_enconderR = {0};
 

void fireMotor_control()//0~2000
{	
	static u8 NO1_temp = 1;
	static u8 NO2_temp = 1;
	if(rc.sl == 1)
	{
		if(NO1_temp == 1)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_2);
			
			GPIO_SetBits(GPIOE, GPIO_Pin_6);
			board_control.set_angle = -30.0f;
			
			if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
			{
				board_control.NO1_keep_time ++;
				buzzer_on();
			}
			
			if(board_control.NO1_keep_time >= 5000)
			{
				buzzer_off();
				GPIO_ResetBits(GPIOE, GPIO_Pin_6);
				NO1_temp = 2;
				board_control.NO1_keep_time = 0;
			}
		}
		else if(NO1_temp == 2)
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_1);
			board_control.set_angle = 45.0f;
		}
	}
	else if(rc.sl == 3)
	{
		if(rc.sr != 3)
		{
			if(NO2_temp == 1)
			{
				GPIO_ResetBits(GPIOF, GPIO_Pin_1);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				
				GPIO_SetBits(GPIOE, GPIO_Pin_6);
				board_control.set_angle = -30.0f;
				
				if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
				{
					buzzer_on();
					board_control.NO2_keep_time ++;
				}
				
				if(board_control.NO2_keep_time >= 3000)
				{
					buzzer_off();
					GPIO_ResetBits(GPIOE, GPIO_Pin_6);
					NO2_temp = 2;
					board_control.NO2_keep_time = 0;
				}
			}
			else if(NO2_temp == 2)
			{
				GPIO_ResetBits(GPIOF, GPIO_Pin_1);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				
				board_control.set_angle = 24.0f;
				GPIO_SetBits(GPIOE, GPIO_Pin_5);
				
				if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
				{
					buzzer_on();
					board_control.NO2_keep_time ++;
				}
				 
				if(board_control.NO2_keep_time >= 3000)
				{
					buzzer_off();
					GPIO_ResetBits(GPIOE, GPIO_Pin_5);
					NO2_temp = 3;
					board_control.NO2_keep_time = 0;
				}
			}
			else if(NO2_temp == 3)
			{
				GPIO_ResetBits(GPIOF, GPIO_Pin_1);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				
				board_control.set_angle = -30.0f;
				GPIO_SetBits(GPIOE, GPIO_Pin_6);
				
				if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
				{
					buzzer_on();
					board_control.NO2_keep_time ++;
				}
				
				if(board_control.NO2_keep_time >= 3000)
				{
					buzzer_off();
					GPIO_ResetBits(GPIOE, GPIO_Pin_6);
					NO2_temp = 4;
					board_control.NO2_keep_time = 0;
				}
			}
			else if(NO2_temp == 4)
			{
				GPIO_ResetBits(GPIOF, GPIO_Pin_1);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				
				board_control.set_angle = 24.0f;
				GPIO_SetBits(GPIOE, GPIO_Pin_5);
				
				if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
				{
					buzzer_on();
					board_control.NO2_keep_time ++;
				}
				
				if(board_control.NO2_keep_time >= 3000)
				{
					buzzer_off();
					GPIO_ResetBits(GPIOE, GPIO_Pin_5);
					NO2_temp = 5;
					board_control.NO2_keep_time = 0;
				}
			}
			else if(NO2_temp == 5)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_2);
				board_control.set_angle = -50.56f;
			}
		}
		else
		{
			if(NO2_temp == 1)
			{
				GPIO_ResetBits(GPIOF, GPIO_Pin_1);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				
				GPIO_SetBits(GPIOE, GPIO_Pin_6);
				board_control.set_angle = -30.0f;
				
				if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
				{
					buzzer_on();
					board_control.NO2_keep_time ++;
				}
				
				if(board_control.NO2_keep_time >= 3000)
				{
					buzzer_off();
					GPIO_ResetBits(GPIOE, GPIO_Pin_6);
					NO2_temp = 2;
					board_control.NO2_keep_time = 0;
				}
			}
			else if(NO2_temp == 2)
			{
				GPIO_ResetBits(GPIOF, GPIO_Pin_1);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				
				board_control.set_angle = 24.0f;
				GPIO_SetBits(GPIOE, GPIO_Pin_5);
				
				if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
				{
					buzzer_on();
					board_control.NO2_keep_time ++;
				}
				 
				if(board_control.NO2_keep_time >= 3000)
				{
					buzzer_off();
					GPIO_ResetBits(GPIOE, GPIO_Pin_5);
					NO2_temp = 3;
					board_control.NO2_keep_time = 0;
				}
			}
			else if(NO2_temp == 3)
			{
				GPIO_ResetBits(GPIOF, GPIO_Pin_1);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				
				board_control.set_angle = -30.0f;
				GPIO_SetBits(GPIOE, GPIO_Pin_6);
				
				if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
				{
					buzzer_on();
					board_control.NO2_keep_time ++;
				}
				
				if(board_control.NO2_keep_time >= 3000)
				{
					buzzer_off();
					GPIO_ResetBits(GPIOE, GPIO_Pin_6);
					NO2_temp = 4;
					board_control.NO2_keep_time = 0;
				}
			}
			else if(NO2_temp == 4)
			{
				GPIO_ResetBits(GPIOF, GPIO_Pin_1);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				
				board_control.set_angle = 24.0f;
				GPIO_SetBits(GPIOE, GPIO_Pin_5);
				
				if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
				{
					buzzer_on();
					board_control.NO2_keep_time ++;
				}
				
				if(board_control.NO2_keep_time >= 3000)
				{
					buzzer_off();
					GPIO_ResetBits(GPIOE, GPIO_Pin_5);
					NO2_temp = 5;
					board_control.NO2_keep_time = 0;
				}
			}
			else if(NO2_temp == 5)
			{
				GPIO_ResetBits(GPIOF, GPIO_Pin_1);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				
				board_control.set_angle = -30.0f;
				GPIO_SetBits(GPIOE, GPIO_Pin_6);
				
				if(fabs(board_control.set_angle - real_angle.roll) <= 5.0f)
				{
					buzzer_on();
					board_control.NO2_keep_time ++;
				}
				
				if(board_control.NO2_keep_time >= 3000)
				{
					buzzer_off();
					GPIO_ResetBits(GPIOE, GPIO_Pin_6);
					NO2_temp = 6;
					board_control.NO2_keep_time = 0;
				}
			}
			else if(NO2_temp == 6)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_2);
				board_control.set_angle = -50.56f;
			}
		}

	}

	if(!(rc.sl == 2))
	{
//		board_control.set_feed = Calculate_Current_Value(&pid[ANGLE_BOARD], board_control.set_angle, real_angle.roll);
//		fire_motor.set_feed = Calculate_Current_Value(&pid[SPEED_BOARD], board_control.set_feed, real_angle.gy);
		
		if(rc.sr != 3)
		{
			board_control.set_feed = Calculate_Current_Value(&pid[ANGLE_BOARD], board_control.set_angle, real_angle.roll);
			fire_motor.set_feed = Calculate_Current_Value(&pid[SPEED_BOARD], board_control.set_feed, real_angle.gy);
		}
		else
		{
			board_control.set_feed = Calculate_Current_Value(&pid[ANGLE_WEIGHT], board_control.set_angle, real_angle.roll);
			fire_motor.set_feed = Calculate_Current_Value(&pid[SPEED_WEIGHT], board_control.set_feed, real_angle.gy);
		}
		
		
		fire_motor.pid_out = fabs(fire_motor.set_feed);
		fire_motor.pid_out = fire_motor.pid_out > 0 ? fire_motor.pid_out : 0;
		fire_motor.pid_out = fire_motor.pid_out < 900 ? fire_motor.pid_out : 900;
		
		if(fire_motor.set_feed > 0)
		{
			TIM1->CCR1 = (int16_t)fire_motor.pid_out + 1100;
			TIM1->CCR4 = (int16_t)0 + 1100;
		}
		
		else if(fire_motor.set_feed < 0)
		{
			TIM1->CCR1 = (int16_t)0 + 1100;
			TIM1->CCR4 = (int16_t)fire_motor.pid_out + 1100;
		}
		else
		{
			TIM1->CCR1 = (int16_t)0 + 1100;
			TIM1->CCR4 = (int16_t)0 + 1100;
		}
	}
	else
	{
		TIM1->CCR1 = (int16_t)0 + 1000;
		TIM1->CCR4 = (int16_t)0 + 1000;
		
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
		GPIO_ResetBits(GPIOE, GPIO_Pin_6);
		GPIO_ResetBits(GPIOE, GPIO_Pin_5);
		GPIO_ResetBits(GPIOF, GPIO_Pin_1);
		
		NO1_temp = 1;
		NO2_temp = 1;
	}
	

}

