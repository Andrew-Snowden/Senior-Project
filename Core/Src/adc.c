/*
 * adc.c
 *
 *  Created on: Mar 15, 2023
 *      Author: andrew
 */

#include "adc.h"


/************************************************************************************************
 *
 * DECLARATIONS
 *
 ***********************************************************************************************/
static void ADC_InitGPIO(void);
static void ADC_Configure(void);
static void ADC_Enable(void);

enum Channel
{
	C_CHANNEL_1,
	C_CHANNEL_2,
	C_CHANNEL_3,
	C_CHANNEL_5
};

static volatile enum Channel channel_state = C_CHANNEL_1;

volatile uint16_t adc_values[4] = {0};

/************************************************************************************************
 *
 * FUNCTIONS
 *
 ***********************************************************************************************/

/** **************************************************************************** *
 * Function Name    	: ADC_Init
 * @brief Description   : This function will be used to configure the entire operational state of ADC3
 *
 * @param				: None
 *
 * @note Precondition	: None
 *
 * @return				: None
 *
 * @note Postcondition	: ADC3 will be running
 *
 ** **************************************************************************** */
void ADC_Init(void)
{


	__HAL_RCC_ADC34_CLK_ENABLE();

	ADC_InitGPIO();

	ADC_Enable();

	ADC_Configure();




}


/** **************************************************************************** *
 * Function Name    	: ADC_Enable
 * @brief Description   : This function will be used to start the ADC. The voltage regulator and calibration is performed
 * 							here.
 *
 * @param				: None
 *
 * @note Precondition	: ADC34 Clock enabled
 *
 * @return				: None
 *
 * @note Postcondition	: ADC3 will be enabled and ready for configuration
 *
 ** **************************************************************************** */
void ADC_Enable(void)
{
	/****************************
	 * Enable voltage regulator *
	 ****************************/

	//Reset and enable voltage regulator
	ADC3->CR = 0;
	ADC3->CR = ADC_CR_ADVREGEN;

	//Wait for regulator to fully turn on
	for (int i = 0; i < 10000; i++)
	{
		__asm volatile("nop");
	}


	/*************
	 * Calibrate *
	 *************/

	//Start ADC Calibration
	ADC3->CR |= ADC_CR_ADCAL;

	//Wait until calibration is finished
	while (ADC3->CR & ADC_CR_ADCAL_Msk);

	//Wait additional 4 cycles according to datasheet
	__asm volatile("nop");
	__asm volatile("nop");
	__asm volatile("nop");
	__asm volatile("nop");


	/***************
	 * Turn ADC on *
	 ***************/

	//Enable ADC
	ADC3->CR |= ADC_CR_ADEN;

	//Wait until ADC is ready
	while ((ADC3->ISR & ADC_ISR_ADRDY_Msk) != 1);

}

/** **************************************************************************** *
 * Function Name    	: ADC_Configure
 * @brief Description   : This function will be used to configure ADC3 registers that will allow
 * 							for correct operation of the ADC. It will configure which interrupts are enabled,
 * 							resolution, and channels.
 *
 * @param				: None
 *
 * @note Precondition	: ADC3 will need to be enabled (ADEN = 1)
 *
 * @return				: None
 *
 * @note Postcondition	: ADC3 will be ready to start conversions. Configured as:
 * 							- Continuous mode
 * 							- Sequence mode
 * 							- Channel 1, 2, 3, 5
 * 							- EOC interrupt enabled
 *
 ** **************************************************************************** */
void ADC_Configure(void)
{
	//Clear interrupts
	uint16_t interrupts = ADC3->ISR;
	ADC3->ISR = interrupts;

	//Enable EOC and EOS interrupts
	ADC3->IER |= ADC_IER_EOCIE | ADC_IER_EOSIE;

	//Configure in continuous mode, overrun overwrite
	ADC3->CFGR |= ADC_CFGR_OVRMOD | ADC_CFGR_AUTDLY;

	//Configure conversion sequence
	ADC3->SQR1 |= 					  4 |
				(1 << ADC_SQR1_SQ1_Pos) |
				(2 << ADC_SQR1_SQ2_Pos) |
				(3 << ADC_SQR1_SQ3_Pos) |
				(5 << ADC_SQR1_SQ4_Pos);

	//Start running the ADC
	ADC3->CR |= ADC_CR_ADSTART;
}

/** **************************************************************************** *
 * Function Name    	: ADC_InitGPIO
 * @brief Description   : This function is used to initialize the GPIO for the ADC channels and ACD3 interrupts
 *
 * @param				: None
 *
 * @note Precondition	: None
 *
 * @return				: None
 *
 * @note Postcondition	: GPIO will be configured for required ADC channels
 *
 ** **************************************************************************** */
void ADC_InitGPIO(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_13;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_13;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(ADC3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC3_IRQn);
}


void ADC3_IRQHandler(void)
{
	if (ADC3->ISR & ADC_ISR_EOC_Msk)
	{
		adc_values[channel_state] = ADC3->DR;

		channel_state++;
	}

	if (ADC3->ISR & ADC_ISR_EOS_Msk)
	{
		//Clear flag
		ADC3->ISR = ADC_ISR_EOS;

		//Reset channel state
		channel_state = C_CHANNEL_1;
	}
}
