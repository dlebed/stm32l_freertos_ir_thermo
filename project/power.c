#include "power.h"

#include "stm32l1xx.h"
#include "FreeRTOS.h"

#include <util.h>

volatile uint8_t current_power_state = POWER_STATE_INIT;
volatile uint8_t new_power_state = POWER_STATE_INIT;

volatile uint32_t currentCPU_HZ	= 2097000UL;

void initPowerSubsystem() {
	RCC_MSIRangeConfig(RCC_MSIRange_4);
	new_power_state = POWER_STATE_MED_SPEED;
	currentCPU_HZ = powerStateClockFrequency(new_power_state);
	SysTick_Config(powerStateClockFrequency(new_power_state) / configTICK_RATE_HZ);
	current_power_state = new_power_state;
	PWR_VoltageScalingConfig(PWR_VoltageScaling_Range3);
	FLASH_SetLatency(FLASH_Latency_0);
	FLASH_PrefetchBufferCmd(DISABLE);
	FLASH_ReadAccess64Cmd(DISABLE);
}

void setPowerState(PowerState state) {
	new_power_state = state;
}

PowerState getPowerState() {
	return current_power_state;
}

void powerStateCheck() {
	if (unlikely(current_power_state != new_power_state)) {
		switch (new_power_state) {
		case POWER_STATE_HI_SPEED:
			// Для более быстрого изменения напряжения питания ядра
			if (current_power_state == POWER_STATE_LOW_SPEED) {
				RCC_MSIRangeConfig(RCC_MSIRange_4);
			}

			PWR_VoltageScalingConfig(PWR_VoltageScaling_Range2);
			RCC_MSIRangeConfig(RCC_MSIRange_6);
			currentCPU_HZ = powerStateClockFrequency(new_power_state);
			SysTick_Config(currentCPU_HZ / configTICK_RATE_HZ);
			break;
		case POWER_STATE_MED_SPEED:
			RCC_MSIRangeConfig(RCC_MSIRange_4);
			currentCPU_HZ = powerStateClockFrequency(new_power_state);
			SysTick_Config(currentCPU_HZ / configTICK_RATE_HZ);

			if (current_power_state == POWER_STATE_HI_SPEED) {
				PWR_VoltageScalingConfig(PWR_VoltageScaling_Range3);
			}

			break;
		case POWER_STATE_LOW_SPEED:
			if (current_power_state == POWER_STATE_HI_SPEED) {
				// Для более быстрого изменения питания ядра
				RCC_MSIRangeConfig(RCC_MSIRange_4);
				PWR_VoltageScalingConfig(PWR_VoltageScaling_Range3);
			}

			// Окончательный переход на другую частоту
			RCC_MSIRangeConfig(RCC_MSIRange_1);
			currentCPU_HZ = powerStateClockFrequency(new_power_state);
			SysTick_Config(currentCPU_HZ / configTICK_RATE_HZ);
			break;
		}

		// Установка нового состояния энергосбережения
		current_power_state = new_power_state;
	}
}


uint32_t powerStateClockFrequency(PowerState state) {
	switch (state) {
	case POWER_STATE_INIT:
		return 4194000UL;
	case POWER_STATE_HI_SPEED:
		return 4194000UL;
	case POWER_STATE_MED_SPEED:
		return 1048000UL;
	case POWER_STATE_LOW_SPEED:
		return 131072UL;
	}
}
