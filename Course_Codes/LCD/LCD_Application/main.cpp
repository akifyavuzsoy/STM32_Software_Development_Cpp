
#include "lcd.h"

int main(void)
{
	HAL_Init();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	pinStruct_t rs = {GPIOD, GPIO_PIN_0};			// RS
	pinStruct_t en = {GPIOD, GPIO_PIN_1};			// EN
	pinStruct_t d4 = {GPIOD, GPIO_PIN_2};			// D4
	pinStruct_t d5 = {GPIOD, GPIO_PIN_3};			// D5
	pinStruct_t d6 = {GPIOD, GPIO_PIN_6};			// D6
	pinStruct_t d7 = {GPIOD, GPIO_PIN_7};			// D7
	
	static LCD lcd(rs,en,d4,d5,d6,d7);
	
	// Example 1:
//	lcd.Print('A');
//	lcd.SetCusor(2,1);
//	lcd.Print("How are you?");
	
	// Example 2:
	uint8_t x = 10;
	uint16_t y = 5600;
	uint32_t z = 1234560;
	
	lcd.Print(x);
	lcd.SetCusor(1,0);
	lcd.Print(y);
	lcd.SetCusor(2,2);
	lcd.Print(z);
	
	// Example 3:
//	lcd.Print("Hello World");
//	HAL_Delay(1000);
//	lcd.Clear();
//	HAL_Delay(1000);
//	lcd.Print("Lovely goal");
//	HAL_Delay(1000);
//	lcd.Clear();
//	HAL_Delay(1000);	
//	uint8_t var = 7;
//	lcd.Print(var);
	
	while(1)
	{
		
	}
}

extern "C" void SysTick_Handler(void)
{
	HAL_IncTick();
}
