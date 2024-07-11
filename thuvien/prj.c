#include "prj.h"
//------------var button------------
uint8_t btn_current = 1;
uint8_t btn_last = 1;
uint8_t btn_filter = 1;
uint8_t is_debouncing;
uint32_t time_deboune;
uint32_t time_stat_press;
uint8_t is_press_timeout;

__weak void btn_callback(GPIO_TypeDef *GPIOx , uint16_t GPIO_Pin)
{
	
}

void button_handle(Button_Typedef *ButtonX)
{
	//-------------- loc nhieu -----------------------
	uint8_t sta = HAL_GPIO_ReadPin(ButtonX -> GPIOx, ButtonX -> GPIO_Pin);
	if (sta != ButtonX -> btn_filter)
	{
		ButtonX -> btn_filter = sta;
		ButtonX -> is_debouncing = 1;
		ButtonX -> time_deboune = HAL_GetTick();
	//----------- xac lap tin hieu ---------------
	}
	if (ButtonX -> is_debouncing && HAL_GetTick() - time_deboune >= 15)
	{
		ButtonX -> btn_current = ButtonX -> btn_filter;
		ButtonX -> is_debouncing = 0;
	}
	//---------------- xu li ---------------
	if (ButtonX -> btn_current != ButtonX -> btn_last)
	{
		if (ButtonX -> btn_current == 0)    
		{
			ButtonX -> is_press_timeout = 1;
			btn_callback(ButtonX -> GPIOx, ButtonX -> GPIO_Pin);
			ButtonX ->time_stat_press = HAL_GetTick();
		}
		ButtonX -> btn_last = ButtonX -> btn_current ;
	}
}
void button_init(Button_Typedef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ButtonX -> GPIOx = GPIOx;
	ButtonX -> GPIO_Pin = GPIO_Pin;
}