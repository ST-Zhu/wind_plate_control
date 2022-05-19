#include "main.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(180);
	BSP_Init();
	IMU_control_decide();

	while(1)
	{
		
	}
}
