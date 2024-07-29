#include "l298n.h"

int main(void)
{
	HAL_Init();
	
	
	while(1)
	{
		
	}
}

extern "C" void SysTick_Handler(void)
{
	HAL_IncTick();
}
