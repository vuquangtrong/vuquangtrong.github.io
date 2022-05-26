#include <stdint.h>

extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _lddata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern void main(void);

void Reset_Handler(void) {
    // copy .data section from flash to ram
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pRAM = (uint8_t*)&_sdata;
    uint8_t *pFlash = (uint8_t*)&_lddata;
    
    for(int i=0; i<size; i++) {
        pRAM[i] = pFlash[i];
    }

    // initialize .bss section
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pRAM = (uint8_t*)&_sbss;

    for(int i=0; i<size; i++) {
        pRAM[i] = 0;
    }

    // call to main
    main();
}
