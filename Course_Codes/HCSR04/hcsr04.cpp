#include "hcsr04.h"

void HCSR04_TrigPinPWMInit(pinStruct_t& trigPin, TIM_TypeDef* TIMx, uint8_t gpioAFSelTIMx, uint8_t pwmChannel)
{
	// GPIO Config
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = trigPin.selectedPin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = gpioAFSelTIMx;
	HAL_GPIO_Init(trigPin.port, &GPIO_InitStruct);
	
	// TIM Config
	TIM_HandleTypeDef htim;
  TIM_OC_InitTypeDef sConfigOC = {0};
  htim.Instance = TIMx;
  htim.Init.Prescaler = 10 - 1;
  htim.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim.Init.Period = 32000 - 1;
  htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_PWM_Init(&htim);
	
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 24;		// 15uS trigger pulse
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, pwmChannel);
	
	// Start PWM Signal
	HAL_TIM_PWM_Start(&htim, pwmChannel);
}

HCSR04::HCSR04(pinStruct_t& echoPin, TIM_TypeDef* TIMx, uint8_t gpioAFSelTIMx)
{
	// GPIO Config
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = echoPin.selectedPin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = gpioAFSelTIMx;
	HAL_GPIO_Init(echoPin.port, &GPIO_InitStruct);
	
	// PWM Input mode config
	
	
}