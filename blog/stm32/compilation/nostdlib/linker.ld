ENTRY(Reset_Handler)

MEMORY
{
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K
  FLASH   (rx)    : ORIGIN = 0x08000000,   LENGTH = 512K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .isr_vector :
    {
        *(.isr_vector)
    } >FLASH

    .text :
    {
        *(.text)
        _etext = .;
    } >FLASH

    .rodata :
    {
        *(.rodata)
    } >FLASH

    _lddata = LOADADDR(.data);
    .data :
    {
        _sdata = .;
        *(.data)
        _edata = .;
    } >RAM AT> FLASH

    .bss :
    {
        _sbss = .;
        *(.bss)
        _ebss = .;
    } >RAM
}
