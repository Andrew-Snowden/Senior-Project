/*
 * encoder.h
 *
 *  Created on: Feb 22, 2023
 *      Author: andre
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f3xx_hal.h"
#include "stm32f303xe.h"

volatile extern int16_t rotary_position;

void RotaryEncoderInit();

#endif /* INC_ENCODER_H_ */
