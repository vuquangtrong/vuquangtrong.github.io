#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx.h>
#include "FreeRTOS.h"
#include "task.h"

/* Override low-level _write system call */
int _write(int file, char *ptr, int len) {
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++) {
        ITM_SendChar(*ptr++);
    }
    return len;
}

TaskHandle_t blinkTaskHandler;
TaskHandle_t logTaskHandler;

void Blink_TaskFunction(void *pvParameters);
void Log_TaskFunction(void *pvParameters);

int main(void)
{
  SystemInit();

  /* turn on clock on GPIOA */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  /* set PA5 to output mode */
  GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
  GPIOA->MODER |=  GPIO_MODER_MODE5_0;

  xTaskCreate(
      Blink_TaskFunction,
      "Blink",
      configMINIMAL_STACK_SIZE,
      NULL,
      1,
      &blinkTaskHandler);

  xTaskCreate(
        Log_TaskFunction,
        "Log",
        configMINIMAL_STACK_SIZE,
        (void *)500,
        1,
        &logTaskHandler);

  vTaskStartScheduler();

  while(1);
}

void Blink_TaskFunction(void *pvParameters) {
  while(1) {
    /* set HIGH value on pin PA5 */
    GPIOA->BSRR |= GPIO_BSRR_BS_5;
    vTaskDelay(250);

    /* set LOW value on pin PA5 */
    GPIOA->BSRR |= GPIO_BSRR_BR_5;
    vTaskDelay(250);
  }
}

void Log_TaskFunction(void *pvParameters) {
  uint8_t counter;
  while(1) {
    printf("counter = %d\n", counter);
    counter++;
    vTaskDelay((TickType_t)pvParameters);
  }
}
