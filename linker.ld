OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH("arm")
ENTRY(_start)

MEMORY
{
    gic     (rw) : ORIGIN = 0x00A00000, LENGTH = 32K
    uart    (rw) : ORIGIN = 0x02020000, LENGTH = 16K
    gpt1    (rw) : ORIGIN = 0x02098000, LENGTH = 16K
    gpio1   (rw) : ORIGIN = 0x0209C000, LENGTH = 16K
    gpio2   (rw) : ORIGIN = 0x020A0000, LENGTH = 16K
    gpio3   (rw) : ORIGIN = 0x020A4000, LENGTH = 16K
    gpio4   (rw) : ORIGIN = 0x020A8000, LENGTH = 16K
    gpio5   (rw) : ORIGIN = 0x020AC000, LENGTH = 16K
    enet2   (rw) : ORIGIN = 0x020B4000, LENGTH = 16K
    ccm     (rw) : ORIGIN = 0x020C4000, LENGTH = 16K
    analog  (rw) : ORIGIN = 0x020C8000, LENGTH = 16K
    iomux   (rw) : ORIGIN = 0x020E0000, LENGTH = 16K
    gpt2    (rw) : ORIGIN = 0x020E8000, LENGTH = 16K
    enet1   (rw) : ORIGIN = 0x02188000, LENGTH = 16K
    ram    (rwx) : ORIGIN = 0x80000000, LENGTH = 0x8000000
}

SECTIONS
{
    /* text/execute section */

    .text : ALIGN(4K)
    {
        *(.entry*)
        *(.text*)
    } >ram

    /* Read only data section */

    .rodata . + (4K) : ALIGN(4K)
    {
        *(.rodata*);
    } >ram

    /* Read/write data section */

    .data . + (4K) : ALIGN(4K)
    {
        *(.data*);
    } >ram

    /* unintialized read/write data section */

    .bss . + (4K) (NOLOAD) : ALIGN(4K)
    {
        PROVIDE(_bss_start = .);
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        PROVIDE(_bss_end = .);
    } >ram

    /* User stack */
    _user_stack_end = LOADADDR(.user_stack) + SIZEOF(.user_stack);

    .user_stack . + (4K) (NOLOAD) : ALIGN(4K)
    {
        . = . + (4K);
    } >ram

    /* Supervisor stack */
    _svc_stack_end = LOADADDR(.svc_stack) + SIZEOF(.svc_stack);

    .svc_stack . + (4K) (NOLOAD) : ALIGN(4K)
    {
        . = . + (4K);
    } >ram

    /* Abort stack */
    _abt_stack_end = LOADADDR(.abt_stack) + SIZEOF(.abt_stack);

    .abt_stack . + (4K) (NOLOAD) : ALIGN(4K)
    {
        . = . + (4K);
    } >ram

    /* Undefined stack */
    _und_stack_end = LOADADDR(.und_stack) + SIZEOF(.und_stack);

    .und_stack . + (4K) (NOLOAD) : ALIGN(4K)
    {
        . = . + (4K);
    } >ram

    /* IRQ stack */
    _irq_stack_end = LOADADDR(.irq_stack) + SIZEOF(.irq_stack);

    .irq_stack . + (4K) (NOLOAD) : ALIGN(4K)
    {
        . = . + (4K);
    } >ram

    /* FIQ stack */
    _fiq_stack_end = LOADADDR(.fiq_stack) + SIZEOF(.fiq_stack);

    .fiq_stack . + (4K) (NOLOAD) : ALIGN(4K)
    {
        . = . + (4K);
    } >ram

    _gic_start = LOADADDR(.gic);

    .gic (NOLOAD) : ALIGN(4K)
    {
        . = . + (32K);
    } >gic

    _uart_start = LOADADDR(.uart);

    .uart (NOLOAD) : ALIGN(4K)
    {
        . = . + (4K);
    } >uart

    _gpt1_start = LOADADDR(.gpt1);

    .gpt1 (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >gpt1

    _gpt2_start = LOADADDR(.gpt2);

    .gpt2 (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >gpt2

    _gpio1_start = LOADADDR(.gpio1);

    .gpio1 (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >gpio1

    _gpio2_start = LOADADDR(.gpio2);

    .gpio2 (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >gpio2

    _gpio3_start = LOADADDR(.gpio3);

    .gpio3 (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >gpio3

    _gpio4_start = LOADADDR(.gpio4);

    .gpio4 (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >gpio4

    _gpio5_start = LOADADDR(.gpio5);

    .gpio5 (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >gpio5

    _ccm_start = LOADADDR(.ccm);

    .ccm (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >ccm

    _analog_start = LOADADDR(.analog);

    .analog (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >analog

    _iomux_start = LOADADDR(.iomux);

    .iomux (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >iomux

    _enet1_start = LOADADDR(.enet1);

    .enet1 (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >enet1

    _enet2_start = LOADADDR(.enet2);

    .enet2 (NOLOAD) : ALIGN(4K)
    {
        . = . + (16K);
    } >enet2
}
