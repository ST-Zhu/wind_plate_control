#ifndef _FIREMOTOR_H_
#define _FIREMOTOR_H_
#include "stm32f4xx.h"

#define FIRE_RATE_BUF_SIZE  5


typedef struct 
{
	float set_feed;
	float pid_out;
}Fire_Motor;

typedef struct 
{
	float set_feed;
	float set_angle;
	uint16_t NO1_keep_time;
	uint16_t NO2_keep_time;
}Board_Control;

typedef struct encoder__
{
    int32_t value;
    int32_t value_last;
    int32_t diff;
    uint8_t buf_count;						 //�˲�����buf��
	int32_t rate_buf[FIRE_RATE_BUF_SIZE];	     //buf��for filter
	int32_t ecd_raw_rate;					 //ͨ������������õ����ٶ�ԭʼֵ
	int32_t filter_rate;					 //�ٶ�
	
}Fire_Enconder;     //������




extern Board_Control board_control;
extern Fire_Motor fire_motor;
extern Fire_Enconder fire_enconderL;
extern Fire_Enconder fire_enconderR;

void fireMotor_control(void);





#endif






