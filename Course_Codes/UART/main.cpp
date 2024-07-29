#include "Controller.h"

#include <stdio.h>
#include "string.h"

#define LED_Pin GPIO_PIN_12
#define LED_GPIO_Port GPIOD

SysController syscontroller; 

UART_HandleTypeDef huart2;

char receiveData[1];
float data3=125.25;
char message[200];

int main(void)
{
	syscontroller.majorVersion = 01;
	syscontroller.minorVersion = 01;
	
	HAL_Init(); 

	Uart uart(&huart2, 115200);
	
	while(1)
	{
		Assign_UartTxBuf(&syscontroller, &uart);
		uart.sentDataToUART(huart2, syscontroller.UART_TX_BUF, BufSize, 100);
		//sprintf(message, "%.3f\n",data3);
	  //HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), 100);
		HAL_Delay(500);
		HAL_UART_Receive(&huart2, (uint8_t *)&receiveData[0],1, 100);
		HAL_Delay(300);
		
	}
}


extern "C" void SysTick_Handler(void)
{
	HAL_IncTick();
}
