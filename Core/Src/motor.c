#include "motor.h"
#include "tim.h"
#include "encoder.h"

//deg/s
float motor_speed = 0;
float previous_motor_speed = 0;

uint8_t ready = 0;

uint32_t motor_force = 0;
enum MotorDirection motor_direction = MD_Right;

void Motor_SetDirection(enum MotorDirection direction)
{
	motor_direction = direction;
	if (direction == MD_Right)
	{
		HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);
	}
	else
	{
		HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_1);
	}

}

void Motor_SetForce(uint32_t force)
{
	motor_force = 150;
	if (force + motor_force > 1000)
	{
		motor_force = 1000;
	}
	else
	{
		motor_force += force;
	}
	motor_force /= 2;

	if (motor_direction == MD_Right)
	{
		__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, motor_force);
	}
	else
	{
		__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, motor_force);
	}
}

void Motor_Start(void)
{
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
	Motor_SetForce(0);
	Motor_SetDirection(MD_Right);
	//LL_TIM_EnableCounter(TIM15);
	ready = 1;
}

void Motor_Stop(void)
{
	ready = 0;
	Motor_SetForce(0);
	HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);
}

uint8_t Motor_IsReady(void)
{
	return ready;
}

float Motor_GetSpeed(void)
{
	return motor_speed;
}

float Motor_GetAcceleration(void)
{
	uint16_t delta = motor_speed - previous_motor_speed;

	return delta * 1000;
}

uint16_t Motor_GetPosition(void)
{
	return rotary_position;
}

//Called every 1ms
void Motor_CalculateSpeed(void)
{
	int16_t delta = (rotary_position - previous_rotary_position);
	previous_rotary_position = rotary_position;

	if (delta < 0) delta *= -1000;
	else delta *= 1000;

	motor_speed = delta / 28;
}





