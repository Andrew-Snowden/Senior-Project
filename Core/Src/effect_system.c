/*
 * EffectSystem.c
 *
 *  Created on: Mar 16, 2023
 *      Author: andrew
 */

#include "effect_system.h"
#include "motor.h"
#include "myprint.h"

volatile struct Effect effects[MAX_EFFECTS] = {0};


/** **************************************************************************** *
 * Function Name    	: ES_CalculateConditionForce
 * @brief Description   : This function will be used to calculate the force based on condition parameters and a metric
 *
 * @param				: metric: Value being tested against (speed, position, acceleration, etc.)
 * 							condition: The condition structure containing relevant information
 *
 * @note Precondition	: None
 *
 * @return				: Calculated force
 *
 * @note Postcondition	: None
 *
 ** **************************************************************************** */
int16_t ES_CalculateConditionForce(int16_t metric, struct Condition condition)
{
	int16_t force = 0;
	if (metric < (condition.center_point_offset - condition.dead_band))
	{
		force = condition.positive_coefficient * (metric - (condition.center_point_offset - condition.dead_band));
	}
	else if (metric > (condition.center_point_offset + condition.dead_band))
	{
		force = condition.positive_coefficient * (metric - (condition.center_point_offset + condition.dead_band));
	}

	return force;
}


float ES_CalculateEnvelope(struct Effect effect)
{
	float scale_factor = 0;

	if (effect.effect_block.duration == 0)
	{
		scale_factor = 1;
	}
	else
	{
		if (effect.tick < effect.envelope.attack_time)
		{
			scale_factor = (float)effect.tick / (float)effect.envelope.attack_time;
		}
		else if (effect.tick < (effect.effect_block.duration + effect.envelope.attack_time))
		{
			scale_factor = 1;
		}
		else if (effect.envelope.fade_time != 0)
		{
			scale_factor = ((float)effect.tick - (effect.effect_block.duration + effect.envelope.attack_time))
							/ (float)effect.envelope.fade_time;
		}
	}

	return scale_factor;
}

/** **************************************************************************** *
 * Function Name    	: ES_CalculateNetForce
 * @brief Description   : This function will be used to calculate the net force acting on the wheel
 *
 * @param				: None
 *
 * @note Precondition	: None
 *
 * @return				: Calculated force
 *
 * @note Postcondition	: None
 *
 ** **************************************************************************** */
volatile int16_t ES_CalculateNetForce(void)
{
	int16_t net_force = 0;
	int16_t present_force = 0;



	for (int i = 0; i < MAX_EFFECTS; i++)
	{
		if (effects[i].running && effects[i].active)
		{

			switch (effects[i].effect_block.effect_type)
			{
			case ET_ConstantForce:

				present_force = (effects[i].constant_force.magnitude * ES_CalculateEnvelope(effects[i]) *-1);

			break;
			case ET_Ramp:

			break;
			case ET_CustomForceData:

			break;
			case ET_Square:
			case ET_Sine:
			case ET_Triangle:
			case ET_SawtoothUp:
			case ET_SawtoothDown:

			break;
			case ET_Spring:

				present_force = ES_CalculateConditionForce(Motor_GetPosition(), effects[i].condition);

			break;
			case ET_Damper:

				present_force = ES_CalculateConditionForce(Motor_GetSpeed(), effects[i].condition);

			break;
			case ET_Inertia:

				present_force = ES_CalculateConditionForce(Motor_GetAcceleration(), effects[i].condition);

			break;
			case ET_Friction:

			break;
			default:
				myprint_dec(1);
			break;
			}

			net_force += present_force * ((float)effects[i].effect_block.gain/100);

		}
	}

	return net_force;
}

/** **************************************************************************** *
 * Function Name    	: ES_AddEffect
 * @brief Description   : This function will be used to add an effect to the effects pool
 *
 * @param				: Effect structure containing relevant effect data
 *
 * @note Precondition	: None
 *
 * @return				: Index of the effect if there was an available slot,
 * 							MAX_EFFECTS to indicate no slot was available
 *
 * @note Postcondition	: None
 *
 ** **************************************************************************** */
uint16_t ES_AddEffect(struct Effect effect)
{
	for (int i = 0; i < MAX_EFFECTS; i++)
	{
		if (effects[i].active != 1)
		{
			effects[i] 					= effect;
			effects[i].active 			= 1;

			return i;
		}
	}

	return MAX_EFFECTS;
}

/** **************************************************************************** *
 * Function Name    	: ES_RemoveEffect
 * @brief Description   : This function will be used to remove an effect from the effect pool
 *
 * @param				: Index of the effect to be removed
 *
 * @note Precondition	: None
 *
 * @return				: None
 *
 * @note Postcondition	: None
 *
 ** **************************************************************************** */
void ES_RemoveEffect(uint16_t index)
{
	if (index < MAX_EFFECTS)
	{
		effects[index].active = 0;
	}
}

/** **************************************************************************** *
 * Function Name    	: ES_StartEffect
 * @brief Description   : This function will be used to start an active effect
 *
 * @param				: Index of the effect to be started
 *
 * @note Precondition	: Effect at index must be active
 *
 * @return				: None
 *
 * @note Postcondition	: None
 *
 ** **************************************************************************** */
void ES_StartEffect(uint16_t index)
{
	if (effects[index].active)
	{
		effects[index].running = 1;
	}
}

/** **************************************************************************** *
 * Function Name    	: ES_StopEffect
 * @brief Description   : This function will be used to stop an active effect
 *
 * @param				: Index of the effect to be stopped
 *
 * @note Precondition	: Effect at index must be active
 *
 * @return				: None
 *
 * @note Postcondition	: None
 *
 ** **************************************************************************** */
void ES_StopEffect(uint16_t index)
{
	if (effects[index].active)
	{
		effects[index].running = 0;
	}
}


void ES_PlayEffects(void)
{
	int16_t force = ES_CalculateNetForce();


	if (force < 0)
	{
		Motor_SetDirection(MD_Right);
		Motor_SetForce(force*-1);
	}
	else
	{
		Motor_SetDirection(MD_Left);
		Motor_SetForce(force);
	}

	for (int i = 0; i < MAX_EFFECTS; i++)
	{
		effects[i].tick++;
		if (effects[i].active && effects[i].running != 1)
		{
			if (effects[i].tick == effects[i].effect_block.trigger_repeat_interval)
			{
				effects[i].running = 1;
				effects[i].tick = 0;
			}
		}
		else if (effects[i].effect_block.duration >= 1 && effects[i].running && effects[i].active)
		{
			if (effects[i].tick >= 	effects[i].envelope.attack_time +
									  effects[i].envelope.fade_time +
									  effects[i].effect_block.duration)
			{
				effects[i].running = 0;
				effects[i].tick = 0;
			}
		}
	}
}
