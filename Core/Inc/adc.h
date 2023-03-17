/*
 * adc.h
 *
 *  Created on: Mar 15, 2023
 *      Author: andre
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32f3xx_hal.h"
#include "stm32f303xe.h"

extern volatile uint16_t adc_values[4];

void ADC_Init(void);

#endif /* INC_ADC_H_ */
