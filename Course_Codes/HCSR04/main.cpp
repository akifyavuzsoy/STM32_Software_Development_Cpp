#include "hcsr04.h"

uint32_t distance = 0;

int main(void)
{
	HAL_Init();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_TIM1_CLK_ENABLE();
	
	// Sensor pins
	pinStruct_t trigPin = {GPIOA, GPIO_PIN_10};
	pinStruct_t echoPin = {GPIOA, GPIO_PIN_8};
	
	HCSR04_TrigPinPWMInit(trigPin, TIM1, GPIO_AF1_TIM1, TIM_CHANNEL_3);
	static HCSR04 hcsr04(echoPin, TIM1, GPIO_AF1_TIM1);
	
	while(1)
	{
		distance = hcsr04.GetDistance();
	}
}

extern "C" void SysTick_Handler(void)
{
	HAL_IncTick();
}
