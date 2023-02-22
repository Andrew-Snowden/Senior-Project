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
	struct  __attribute__((packed)){
		uint8_t buttons;
		uint8_t throttle;
		uint8_t brake;
		int16_t steering;
	} members;
	uint8_t data[5];
} Report;

extern Report report;
/*
 * FUNCTIONS
 */

void myusb_Initialize(void);



#endif /* INC_MYUSB_H_ */
