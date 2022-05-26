#include <stdint.h>
#include <stdio.h>
#include "delay.h"

/* Clock */
#define RCC_AHB1ENR     *((volatile uint32_t*) (0x40023830))

/* GPIO A */
#define GPIOA_MODER     *((volatile uint32_t*) (0x40020000))
#define GPIOA_BSRR      *((volatile uint32_t*) (0x40020018))

/* Global initialized variable */
uint32_t isLoop = 1;

#ifdef USE_SEMIHOSTING
/* Semohosting */
extern void initialise_monitor_handles(void);
#endif

int main() {
    char counter = 0;

#ifdef USE_SEMIHOSTING
    initialise_monitor_handles();
#endif

    /* turn on clock on GPIOA */
    RCC_AHB1ENR |= (1 << 0);

    /* set PA5 to output mode */
    GPIOA_MODER &= ~(1 << 11);
    GPIOA_MODER |=  (1 << 10);

    while(isLoop) {
        /* set HIGH on PA5 */
        GPIOA_BSRR |= (1 << 5);
        delay();

        /* set LOW on PA5 */
        GPIOA_BSRR |= (1 << (5+16));
        delay();
		
        /* output */
        printf("counter = %d\n", counter);
        counter++;
    }
    return 0;
}
