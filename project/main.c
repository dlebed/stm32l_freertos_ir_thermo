#include <main.h>

#include "FreeRTOS.h"
#include "task.h"

#include <stdint.h>

#include <power.h>
#include <hd44780.h>



void vTaskLED1(void *pvParameters) {

        for (;;) {
//                GPIO_SetBits(GPIOB, GPIO_Pin_0);
        		setPowerState(POWER_STATE_HI_SPEED);
                vTaskDelay(50 / portTICK_RATE_MS);
                setPowerState(POWER_STATE_LOW_SPEED);
  //              GPIO_ResetBits(GPIOB, GPIO_Pin_0);
                vTaskDelay(50 / portTICK_RATE_MS);
                setPowerState(POWER_STATE_MED_SPEED);
                vTaskDelay(50 / portTICK_RATE_MS);
        }

}

void vTaskLED2(void *pvParameters) {
	vTaskDelay(1000 / portTICK_RATE_MS);


        for (;;) {
        	//if (clockState == CLOCK_4M)
                GPIO_SetBits(GPIOB, GPIO_Pin_1);

        	vTaskDelay(200 / portTICK_RATE_MS);

        	//if (clockState == CLOCK_4M)
                GPIO_ResetBits(GPIOB, GPIO_Pin_1);

            vTaskDelay(10 / portTICK_RATE_MS);
        }

}

void  Init_GPIOs (void)
{
  /* GPIO, EXTI and NVIC Init structure declaration */
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* Configure the LED_pin as output push-pull for LD3 & LD4 usage*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Force a low level on LEDs*/
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
  GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);
  GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);

  /*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);*/

}

int main(void) {

	initPowerSubsystem();

	/* Enable the GPIOs clocks */
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC| RCC_AHBPeriph_GPIOD| RCC_AHBPeriph_GPIOE| RCC_AHBPeriph_GPIOH, ENABLE);

	Init_GPIOs();

	//xTaskCreate(vTaskLED1, ( signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, 1, ( xTaskHandle * ) NULL);
	xTaskCreate(vTaskLED2, ( signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, 1, ( xTaskHandle * ) NULL);

	vTaskStartScheduler();

	initHD44780();
	//disableHD44780();

	while (1) {
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}


void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	volatile uint16_t i;

	while (1) {
		GPIO_SetBits(GPIOB, GPIO_Pin_0);

		for (int i = 0; i < 10000; i++) {}

		GPIO_ResetBits(GPIOB, GPIO_Pin_0);

		for (int i = 0; i < 10000; i++) {}
	}
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	volatile uint16_t i;

	while (1) {
		GPIO_SetBits(GPIOB, GPIO_Pin_1);

		for (int i = 0; i < 20000; i++) {}

		GPIO_ResetBits(GPIOB, GPIO_Pin_1);

		for (int i = 0; i < 20000; i++) {}
	}
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	__WFI();
}

void vApplicationTickHook(void) {
	//GPIOB->BSRRL = GPIO_BSRR_BS_0;

	/*if (clockState == CLOCK_WAIT_4M) {
		clockState = CLOCK_4M;

		GPIOA->BSRRL = GPIO_BSRR_BS_2;
		GPIOA->BSRRH = GPIO_BSRR_BS_2;
		//RCC_MSIRangeConfig(RCC_MSIRange_4);
		//GPIOA->BSRRL = GPIO_BSRR_BS_2;
		//GPIOA->BSRRH = GPIO_BSRR_BS_2;
		//PWR_VoltageScalingConfig(PWR_VoltageScaling_Range2);
		//GPIOA->BSRRL = GPIO_BSRR_BS_2;
		//GPIOA->BSRRH = GPIO_BSRR_BS_2;
		RCC_MSIRangeConfig(RCC_MSIRange_6);
		GPIOA->BSRRL = GPIO_BSRR_BS_2;
		GPIOA->BSRRH = GPIO_BSRR_BS_2;






		SysTick_Config(4200000UL / configTICK_RATE_HZ);
	} else if (clockState == CLOCK_WAIT_2M) {
		clockState = CLOCK_2M;
		//GPIOA->BSRRL = GPIO_BSRR_BS_2;
		//GPIOA->BSRRH = GPIO_BSRR_BS_2;
		RCC_MSIRangeConfig(RCC_MSIRange_4);
		//GPIOA->BSRRL = GPIO_BSRR_BS_2;
		//GPIOA->BSRRH = GPIO_BSRR_BS_2;
		PWR_VoltageScalingConfig(PWR_VoltageScaling_Range3);
		//GPIOA->BSRRL = GPIO_BSRR_BS_2;
		//GPIOA->BSRRH = GPIO_BSRR_BS_2;
		RCC_MSIRangeConfig(RCC_MSIRange_1);
		//GPIOA->BSRRL = GPIO_BSRR_BS_2;
		//GPIOA->BSRRH = GPIO_BSRR_BS_2;
		SysTick_Config(131000UL / configTICK_RATE_HZ);
	}*/

}
