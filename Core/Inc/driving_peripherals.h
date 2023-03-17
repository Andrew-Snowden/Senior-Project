/*
 * driving_peripherals.h
 *
 *  Created on: Mar 15, 2023
 *      Author: andre
 */

#ifndef INC_DRIVING_PERIPHERALS_H_
#define INC_DRIVING_PERIPHERALS_H_

#include "stdint.h"


//Can possibly use USB Feature reports to set scale_factor, pre_deadzone, and post_deadzone from host

struct Pedal
{
	volatile uint16_t* value;	//Value of axis position (from ADC or hall-effect sensor)
	int16_t offset;				//Offset from read result. Used to fix issue where pedal at 0% != 0 from ADC
	float scale_factor;			//To fix undershoot/overshoot issues. Maximize utilization of range. Prefer overshoot
};

extern struct Pedal throttle;
extern struct Pedal brake;
extern struct Pedal clutch;
extern struct Pedal handbrake;

uint16_t Pedal_GetAxisValue(struct Pedal pedal);

#endif /* INC_DRIVING_PERIPHERALS_H_ */
