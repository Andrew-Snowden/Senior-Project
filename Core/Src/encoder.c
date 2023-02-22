#include "encoder.h"
#include "myprint.h"

volatile int16_t rotary_position;

void RotaryEncoderInit()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	//Set up GPIO PF1 and PF3
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}

void EXTI3_IRQHandler(void) {

	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);

	myprint("PRINT PRINT PRINT PLEASE WORK\r\n");

	if (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_2))	//Forward
	{
		rotary_position++;
	}
	else		//Backward
	{
		rotary_position--;
	}

}
