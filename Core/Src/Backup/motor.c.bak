#include "motor.h"
#include "tim.h"

uint32_t motor_speed = 0;

void Motor_SetDirection(enum MotorDirection direction)
{
	/*
	if (direction == MD_Right)
	{
		LL_TIM_CC_DisableChannel(TIM3, LL_TIM_CHANNEL_CH3);
		LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH4);
	}
	else
	{
		LL_TIM_CC_DisableChannel(TIM3, LL_TIM_CHANNEL_CH4);
		LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH3);
	}
	*/
}

void Motor_SetSpeed(uint32_t speed)
{
	if (speed > 1000)
	{
		motor_speed = 1000;
	}
	else
	{
		motor_speed = speed;
	}
/*
	LL_TIM_OC_SetCompareCH3(TIM3, motor_speed);
	LL_TIM_OC_SetCompareCH4(TIM3, motor_speed);
	*/
}

void Motor_Start()
{
	Motor_SetSpeed(0);
	Motor_SetDirection(MD_Right);
	//LL_TIM_EnableCounter(TIM3);
}

void Motor_Stop()
{
	/*
	LL_TIM_CC_DisableChannel(TIM3, LL_TIM_CHANNEL_CH3);
	LL_TIM_CC_DisableChannel(TIM3, LL_TIM_CHANNEL_CH4);
	LL_TIM_DisableCounter(TIM3);
	*/
}
