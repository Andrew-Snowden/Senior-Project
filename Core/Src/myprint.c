#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void myprint(char* string)
{
	uint8_t buffer[200];
	uint16_t len = strlen(string);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = string[i];
	}

	HAL_UART_Transmit(&huart3, buffer, len, 0xFFFF);
}

void myprint_hex(int reg)
{
	char buffer[20];
	for (int i = 0; i < 20; i++)
	{
		buffer[i] = '\0';
	}
	itoa(reg, buffer, 16);
	HAL_UART_Transmit(&huart3, buffer, 20, 0xFFFF);

	myprint("\r\n");
}

void myprint_dec(int reg)
{
	char buffer[20];
	for (int i = 0; i < 20; i++)
	{
		buffer[i] = '\0';
	}
	itoa(reg, buffer, 10);
	HAL_UART_Transmit(&huart3, buffer, 20, 0xFFFF);

	myprint("\r\n");
}

