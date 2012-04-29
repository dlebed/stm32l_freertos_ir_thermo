#ifndef POWER_H_
#define POWER_H_

#include "stdint.h"

typedef enum {
	POWER_STATE_INIT			=	0x00,
	POWER_STATE_HI_SPEED		=	0x01,
	POWER_STATE_MED_SPEED		=	0x02,
	POWER_STATE_LOW_SPEED		=	0x03
} PowerState;

void initPowerSubsystem();

void setPowerState(PowerState state);

PowerState getPowerState();

void powerStateCheck();

uint32_t powerStateClockFrequency(PowerState state);


#endif /* POWER_H_ */
