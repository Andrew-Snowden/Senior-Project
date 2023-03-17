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
extern float motor_speed;

//Defines
enum MotorDirection
{
	MD_Right,
	MD_Left
};


//Functions
void Motor_SetDirection(enum MotorDirection direction);
void Motor_SetForce(uint32_t force);
void Motor_Start(void);
void Motor_Stop(void);
float Motor_GetSpeed(void);
float Motor_GetAcceleration(void);
uint16_t Motor_GetPosition(void);

void Motor_CalculateSpeed(void);
uint8_t Motor_IsReady(void);





#endif /* SRC_MOTOR_H_ */
