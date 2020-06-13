OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH("arm")
ENTRY(_start)

SECTIONS
{
    . = 0x80000000;

    /* text/execute section */

    . = ALIGN(0x1000);

    .text :
    {
        *(.entry*)
        *(.text*)
    }

    /* Read only data section */

    . = ALIGN(0x1000);

    .rodata :
    {
        *(.rodata*);
    }

    /* Read/write data section */

    . = ALIGN(0x1000);

    .data :
    {
        *(.data*);
    }

    /* unintialized read/write data section */

    . = ALIGN(0x1000);

    .bss (NOLOAD) :
    {
        PROVIDE(_bss_start = .);
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        PROVIDE(_bss_end = .);
    }

    /* Supervisor stack */

    . = ALIGN(0x1000);

    .svc_stack (NOLOAD) :
    {
        PROVIDE(_svc_stack_start = .);
        . = . + (0x1000);
        . = ALIGN(8);
        PROVIDE(_svc_stack_end = .);
    }

    /* Abort stack */
    
    .abt_stack (NOLOAD) :
    {
        PROVIDE(_abt_stack_start = .);
        . = . + (0x1000);
        . = ALIGN(8);
        PROVIDE(_abt_stack_end = .);
    }

    /* Undefined stack */

    .und_stack (NOLOAD) :
    {
        PROVIDE(_und_stack_start = .);
        . = . + (0x1000);
        . = ALIGN(8);
        PROVIDE(_und_stack_end = .);
    }

    /* IRQ stack */

    .irq_stack (NOLOAD) :
    {
        PROVIDE(_irq_stack_start = .);
        . = . + (0x1000);
        . = ALIGN(8);
        PROVIDE(_irq_stack_end = .);
    }

    /* FIQ stack */

    .fiq_stack (NOLOAD) :
    {
        PROVIDE(_fiq_stack_start = .);
        . = . + (0x1000);
        . = ALIGN(8);
        PROVIDE(_fiq_stack_end = .);
    }
}
