/*
 * motor.h
 *
 *  Created on: Jan 13, 2023
 *      Author: andre
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_

#include <stdint.h>

//Variables
//extern uint32_t motor_speed;

//Defines
enum MotorDirection
{
	MD_Right,
	MD_Left
};

//Functions
void Motor_SetDirection(enum MotorDirection direction);
void Motor_SetSpeed(uint32_t speed);
void Motor_Start();
void Motor_Stop();

#endif /* SRC_MOTOR_H_ */
