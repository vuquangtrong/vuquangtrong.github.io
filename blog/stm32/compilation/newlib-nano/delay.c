#include <stdint.h>

/* Global Read-only variable */
const uint32_t DELAY_MAX = 0x000BEEF0;

/* Global Uninitialized varible */
uint32_t delay_counter;

void delay() {
    for(delay_counter=DELAY_MAX; delay_counter--;);
}
