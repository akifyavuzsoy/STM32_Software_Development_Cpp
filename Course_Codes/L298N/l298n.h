#ifndef L298N_H
#define L298N_H

#include "pinmap.h"

enum 
{
	MOTOR_ONEEIGHTHSPEED = 4000,
	MOTOR_QUARTERSPEED = 8000,
	MOTOR_HALFSPEED = 16000,
	MOTOR_FULLSPEED = 32000
};

class L298N
{
	private:
		pinStruct_t Mpin1;
		pinStruct_t Mpin2;
		TIM_HandleTypeDef htim;
		uint8_t pwmCh;
	
	public:
		L298N(pinStruct_t& motorPin1, pinStruct_t& motorPin2, pinStruct_t& pwmPin, TIM_TypeDef* TIMx, uint8_t gpioAFSelTIMx, uint8_t pwmChannel);
		void MoveForward(uint32_t speed);
		void Reverse(uint32_t speed);
		void Stop(void);
};

#endif //L298N_H

