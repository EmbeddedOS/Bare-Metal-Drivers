ENTRY(Reset_Handler)        /* This will be add to header of ELF file to determine
                             * entry of our program. */

MEMORY
{
    FLASH(rx): ORIGIN =0x08000000, LENGTH =1024K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH =128K
}

SECTIONS
{
    .text :
    {
        *(.isr_vector)      /* First of `.text` section will be ISR vector table.   */
        *(.text)            /* Merge `.text` section of all input files.            */
        *(.rodata)          /* Next one will be read only data section.             */
        . = ALIGN(0x4);     /* Align _end_of_text symbol.                           */
        _end_of_text = .;   /* Make a symbol that store end of text address.        */
    }> FLASH                /* Load this section in FLASH memory.                   */

    .data :
    {
        _start_of_data = .; /* Capture start of `.data` section in vma to symbol.   */
        *(.data)
        . = ALIGN(0x4);     /* Align _end_of_data symbol.                           */
        _end_of_data = .;   /* Capture end of `.data` section in vma to the symbol. */
    }> SRAM AT> FLASH       /* VMA is SRAM and LMA is FLASH.                        */

    .bss :
    {
        _start_of_bss = .;  /* Capture start of `.bss` section in vma to symbol.    */
        *(.bss)
        *(COMMON)
        . = ALIGN(0x4);     /* Align _end_of_bss symbol.                            */
        _end_of_bss = .;    /* Capture end of `.bss` section in vma to symbol.      */
    }> SRAM
}