#ifndef UTIL_H_
#define UTIL_H_

#include "stm32l1xx.h"

#ifdef __GNUC__
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
#else
#define likely(x)       (x)
#define unlikely(x)     (x)
#endif

inline void atomicGPIOSetOutDir(GPIO_TypeDef * port, uint8_t pin) {
	uint32_t oldValue, newValue;

	do {
		oldValue = __LDREXW(&(port->MODER));
		newValue = oldValue & ~(GPIO_MODER_MODER0 << (pin * 2));
		newValue |= ((uint32_t)GPIO_Mode_OUT) << (pin * 2);
	} while (__STREXW(newValue, &(port->MODER)));
}

inline void atomicGPIOSetInDir(GPIO_TypeDef * port, uint8_t pin) {
	uint32_t oldValue, newValue;

	do {
		oldValue = __LDREXW(&(port->MODER));
		newValue = oldValue & ~(GPIO_MODER_MODER0 << (pin * 2));
		newValue |= ((uint32_t)GPIO_Mode_IN) << (pin * 2);
	} while (__STREXW(newValue, &(port->MODER)));
}

inline void atomicGPIOGroupSetDir(GPIO_TypeDef * port, uint32_t pinsModeMask, uint32_t newModeMask) {
	uint32_t oldValue, newValue;

	do {
		oldValue = __LDREXW(&(port->MODER));
		newValue = oldValue & ~(pinsModeMask);
		newValue |= newModeMask;
	} while (__STREXW(newValue, &(port->MODER)));
}

#endif /* UTIL_H_ */
