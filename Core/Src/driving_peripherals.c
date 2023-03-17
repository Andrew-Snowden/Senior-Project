/*
 * driving_peripherals.c
 *
 *  Created on: Mar 15, 2023
 *      Author: andre
 */
#include "driving_peripherals.h"
#include "adc.h"

struct Pedal throttle 		= { adc_values, 0, 1 };
struct Pedal brake	 		= { adc_values + 1, 0, 1 };
struct Pedal clutch 		= { adc_values + 2, 0, 1};
struct Pedal handbrake		= { adc_values + 3, 0, 1};

uint16_t Pedal_GetAxisValue(struct Pedal pedal)
{
	//Apply offset and scaling
	int16_t value = *(pedal.value);

	value += pedal.offset;

	if (value < 0)
	{
		value = 0;
	}

	value *= pedal.scale_factor;

	return (uint16_t)value;
}


