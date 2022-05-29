#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
#include "stm32f4xx.h"

extern uint32_t SystemCoreClock;

/* Scheduler settings */
#define configUSE_PREEMPTION    ( 1 )
#define configCPU_CLOCK_HZ      ( SystemCoreClock )
#define configTICK_RATE_HZ      ( ( TickType_t ) 1000 )
#define configUSE_16_BIT_TICKS  ( 0 )   /* use 32-bit */

/* Task settings */
#define configMAX_PRIORITIES        ( 5 )
#define configMINIMAL_STACK_SIZE    ( ( unsigned short ) 130 )
#define configTOTAL_HEAP_SIZE       ( ( size_t ) ( 75 * 1024 ) )
#define configMAX_TASK_NAME_LEN     ( 10 )

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES             ( 0 )
#define configMAX_CO_ROUTINE_PRIORITIES   ( 2 )

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                 ( 0 )
#define configUSE_TICK_HOOK                 ( 0 )
#define configCHECK_FOR_STACK_OVERFLOW      ( 0 )
#define configUSE_MALLOC_FAILED_HOOK        ( 0 )
#define configUSE_DAEMON_TASK_STARTUP_HOOK  ( 0 )

/* Optional functions */
#define INCLUDE_vTaskDelay  ( 1 )

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
  /* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
  #define configPRIO_BITS   __NVIC_PRIO_BITS
#else
  #define configPRIO_BITS   ( 4 )   /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         ( 0xf )

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    ( 5 )

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY         \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT(x)     \
    if((x) == 0) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler         SVC_Handler
#define xPortPendSVHandler      PendSV_Handler
#define xPortSysTickHandler     SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
