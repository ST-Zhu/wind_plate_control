#ifndef __PWM_H__
#define __PWM_H__

#include "main.h"


void TIM1_FireMotor_Configure(void);
void TIM3_Init(uint16_t arr, uint16_t psc);
void heat_output(uint16_t pwm);
#endif

