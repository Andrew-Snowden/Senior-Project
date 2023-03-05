/*
 * myusb.h
 *
 *  Created on: Feb 13, 2023
 *      Author: andre
 */

#ifndef INC_MYUSB_H_
#define INC_MYUSB_H_

#include "stm32f3xx_hal.h"
#include "stm32f303xe.h"

/*
 * DEFINITIONS
 */

typedef union
{
	struct __attribute__((__packed__))
	{
		uint8_t report_id;
		uint8_t buttons_low;
		uint8_t buttons_mid;
		uint8_t buttons_high;
		uint8_t throttle;
		uint8_t brake;
		uint8_t clutch;
		uint8_t handbrake;
		int16_t steering;
	} members;
	uint8_t data[10];
} Report;

extern Report report;
/*
 * FUNCTIONS
 */

void myusb_Initialize(void);



#endif /* INC_MYUSB_H_ */
