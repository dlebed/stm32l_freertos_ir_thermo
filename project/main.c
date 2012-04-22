#include <main.h>

#include "FreeRTOS.h"
#include "task.h"

#include <stdint.h>

void vTaskLED1(void *pvParameters) {

        for (;;) {
                GPIO_SetBits(GPIOB, GPIO_Pin_0);
                vTaskDelay(500);
                GPIO_ResetBits(GPIOB, GPIO_Pin_0);
                vTaskDelay(500);
        }

}

void vTaskLED2(void *pvParameters) {

        for (;;) {
                GPIO_SetBits(GPIOB, GPIO_Pin_1);
                vTaskDelay(500);
                GPIO_ResetBits(GPIOB, GPIO_Pin_1);
                vTaskDelay(500);
        }

}

void  Init_GPIOs (void)
{
  /* GPIO, EXTI and NVIC Init structure declaration */
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* Configure the LED_pin as output push-pull for LD3 & LD4 usage*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Force a low level on LEDs*/
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
  GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);





}

int main(void) {

	/* Enable the GPIOs clocks */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC| RCC_AHBPeriph_GPIOD| RCC_AHBPeriph_GPIOE| RCC_AHBPeriph_GPIOH, ENABLE);

	Init_GPIOs();

	xTaskCreate(vTaskLED1, ( signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, 2, ( xTaskHandle * ) NULL);
	xTaskCreate(vTaskLED2, ( signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, 2, ( xTaskHandle * ) NULL);

	vTaskStartScheduler();

	while (1) {

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

}

void vApplicationTickHook(void) {


}
