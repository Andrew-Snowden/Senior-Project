#include "motor.h"
#include "tim.h"

uint32_t motor_speed = 0;
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

void Motor_SetSpeed(uint32_t speed)
{
	motor_speed = 150;
	if (speed + motor_speed > 1000)
	{
		motor_speed = 1000;
	}
	else
	{
		motor_speed += speed;
	}
	motor_speed /= 2;

	if (motor_direction == MD_Right)
	{
		__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, motor_speed);
	}
	else
	{
		__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, motor_speed);
	}
}

void Motor_Start()
{
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
	Motor_SetSpeed(0);
	Motor_SetDirection(MD_Right);
	//LL_TIM_EnableCounter(TIM15);
}

void Motor_Stop()
{
	Motor_SetSpeed(0);
	HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);
}
