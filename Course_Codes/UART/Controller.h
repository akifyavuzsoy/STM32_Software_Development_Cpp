#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "uart.h"

#define BufSize 128

typedef struct {
	uint8_t majorVersion;
	uint8_t minorVersion;
	
	unsigned char UART_RX_BUF[BufSize];
	unsigned char UART_TX_BUF[BufSize];
	
}SysController;

void Error_Handler(void);
void HAL_MspInit(void);
void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);

void Assign_UartTxBuf(SysController* controller, Uart* uart);


#endif // CONTROLLER_H
