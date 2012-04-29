#include <hd44780.h>

#include "stm32l1xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include <util.h>

xTaskHandle hd44780TaskHandle;

#define HD44780_RS_PORT			GPIOB
#define HD44780_RS_PIN			10
#define HD44780_RS_SET_LOW		(GPIOB->BSRRH = GPIO_BSRR_BS_10)
#define HD44780_RS_SET_HI		(GPIOB->BSRRL = GPIO_BSRR_BS_10)

#define HD44780_RW_PORT			GPIOB
#define HD44780_RW_PIN			11
#define HD44780_RW_SET_LOW		(GPIOB->BSRRH = GPIO_BSRR_BS_11)
#define HD44780_RW_SET_HI		(GPIOB->BSRRL = GPIO_BSRR_BS_11)

#define HD44780_E_PORT			GPIOA
#define HD44780_E_PIN			8
#define HD44780_E_SET_LOW		(GPIOA->BSRRH = GPIO_BSRR_BS_8)
#define HD44780_E_SET_HI		(GPIOA->BSRRL = GPIO_BSRR_BS_8)

#define HD44780_DATA_PORT		GPIOB
#define HD44780_DATA_OFFSET		12
#define HD44780_DATA_MASK		0x0F
#define HD44780_DATA_DIR_MASK	((GPIO_MODER_MODER0 << (12*2)) | (GPIO_MODER_MODER0 << (13*2)) | (GPIO_MODER_MODER0 << (14*2)) | (GPIO_MODER_MODER0 << (15*2)))
#define HD44780_DATA_DIR_OUT_MASK	((((uint32_t)GPIO_Mode_IN) << (12*2)) | (((uint32_t)GPIO_Mode_IN) << (13*2)) | (((uint32_t)GPIO_Mode_IN) << (14*2)) | (((uint32_t)GPIO_Mode_IN) << (15*2)))
#define HD44780_DATA_DIR_OUT_MASK	((((uint32_t)GPIO_Mode_OUT) << (12*2)) | (((uint32_t)GPIO_Mode_OUT) << (13*2)) | (((uint32_t)GPIO_Mode_OUT) << (14*2)) | (((uint32_t)GPIO_Mode_OUT) << (15*2)))

#define HD44780_PWR_SET_OFF		(GPIOB->BSRRH = GPIO_BSRR_BS_6)
#define HD44780_PWR_SET_ON		(GPIOB->BSRRL = GPIO_BSRR_BS_6)

inline void hd44780SetData(uint8_t data) {
	uint16_t oldValue, newValue;

	do {
		oldValue = __LDREXH(&(HD44780_DATA_PORT->ODR));
		newValue = oldValue & ~(HD44780_DATA_MASK << HD44780_DATA_OFFSET);
		newValue |= (data & HD44780_DATA_MASK) << HD44780_DATA_OFFSET;
	} while(__STREXH(newValue, &(HD44780_DATA_PORT->ODR)));
}



void vTaskHD44780LCD(void *pvParameters) {

        while (1) {
        	// Process message queue

        	HD44780_PWR_SET_ON;
            vTaskDelay(10 / portTICK_RATE_MS);
            HD44780_PWR_SET_OFF;
        }

}

void initHD44780() {

	initHD44780GPIO();
	enableHD44780();
	initHD44780ContrastPWM();
	xTaskCreate(vTaskHD44780LCD, ( signed char * ) "HD44780_LCD", configMINIMAL_STACK_SIZE * 2, NULL, 2, ( xTaskHandle * ) &hd44780TaskHandle);

}

void freeHD44780() {
	disableHD44780();
	vTaskDelete( hd44780TaskHandle );
}

void enableHD44780() {
	GPIOB->BSRRH = GPIO_BSRR_BS_7;
}

void disableHD44780() {
	GPIOB->BSRRL = GPIO_BSRR_BS_7;
}

void initHD44780GPIO() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void initHD44780ContrastPWM() {

}

void stopHD44780ContrastPWM() {

}
