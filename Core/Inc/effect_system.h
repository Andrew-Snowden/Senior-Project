/*
 * EffectSystem.h
 *
 *  Created on: Mar 16, 2023
 *      Author: andre
 */

#ifndef INC_EFFECT_SYSTEM_H_
#define INC_EFFECT_SYSTEM_H_

#include "stdint.h"

#define MAX_EFFECTS 10

enum EffectTypes
{
	ET_ConstantForce = 0,
	ET_Ramp,
	ET_CustomForceData,
	ET_Square,
	ET_Sine,
	ET_Triangle,
	ET_SawtoothUp,
	ET_SawtoothDown,
	ET_Spring,
	ET_Damper,
	ET_Inertia,
	ET_Friction
};

struct Envelope
{
	uint16_t attack_level;
	uint16_t attack_time;	//1ms increments
	uint16_t fade_level;
	uint16_t fade_time;		//1ms increments
};

struct Periodic
{
	uint16_t offset;
	int16_t magnitude;
	uint8_t phase;
	uint16_t period;		//1ms increments
};

struct Ramp
{
	int16_t ramp_start;
	int16_t ramp_end;
};

struct ConstantForce
{
	int16_t magnitude;
};

struct Condition
{
	int16_t center_point_offset;
	float positive_coefficient;
	float negative_coefficient;
	int16_t positive_saturation;
	int16_t negative_saturation;
	int16_t dead_band;
};

struct EffectBlock
{
	uint16_t sample_period;				//1ms increments
	uint16_t duration;					//1ms increments
	uint8_t effect_type;
	uint16_t trigger_repeat_interval;	//1ms increments
	uint8_t gain;
};

struct Effect
{
	struct EffectBlock effect_block;
	struct Envelope envelope;
	struct Condition condition;
	struct Periodic periodic;
	struct Ramp ramp;
	struct ConstantForce constant_force;
	uint8_t running;
	uint8_t active;
	uint16_t tick;		//1ms increments
};

extern volatile struct Effect effects[MAX_EFFECTS];

int16_t ES_CalculateConditionForce(int16_t metric, struct Condition condition);
float ES_CalculateEnvelope(struct Effect effect);
int16_t ES_CalculateNetForce(void);
uint16_t ES_AddEffect(struct Effect effect);
void ES_RemoveEffect(uint16_t index);
void ES_StartEffect(uint16_t index);
void ES_StopEffect(uint16_t index);
void ES_PlayEffects(void);


#endif /* INC_EFFECT_SYSTEM_H_ */
