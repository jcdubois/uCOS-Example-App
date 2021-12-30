OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH("arm")
ENTRY(_start)

MEMORY
{
    ocram  (rwx) : ORIGIN = 0x00900000, LENGTH = 128K
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
    iomux_g (rw) : ORIGIN = 0x020E4000, LENGTH = 16K
    gpt2    (rw) : ORIGIN = 0x020E8000, LENGTH = 16K
    enet1   (rw) : ORIGIN = 0x02188000, LENGTH = 16K
    nvram   (rw) : ORIGIN = 0x50000000, LENGTH = 256K
    ram    (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{
    /* text/execute section */
    .text :
    {
        *(.entry*)
        *(.text*)
    } >ram

    /* Read only data section */

    .rodata (ALIGN(4K) + (4K)) :
    {
        *(.rodata*);
    } >ram

    /* Read/write data section */

    .data (ALIGN(4K) + (4K)) :
    {
        *(.data*);
    } >ram

    _prog_size = ADDR(.data) + SIZEOF(.data) - ADDR(.text);

    /* unintialized read/write data section */

    .bss (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        PROVIDE(_bss_start = .);
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        PROVIDE(_bss_end = .);
    } >ram

    /* User stack */
    _user_stack_end = ADDR(.user_stack) + SIZEOF(.user_stack);

    .user_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . = . + (4K);
    } >ram

    /* Supervisor stack */
    _svc_stack_end = ADDR(.svc_stack) + SIZEOF(.svc_stack);

    .svc_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . = . + (4K);
    } >ram

    /* Abort stack */
    _abt_stack_end = ADDR(.abt_stack) + SIZEOF(.abt_stack);

    .abt_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . = . + (4K);
    } >ram

    /* Undefined stack */
    _und_stack_end = ADDR(.und_stack) + SIZEOF(.und_stack);

    .und_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . = . + (4K);
    } >ram

    /* IRQ stack */
    _irq_stack_end = ADDR(.irq_stack) + SIZEOF(.irq_stack);

    .irq_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . = . + (4K);
    } >ram

    /* FIQ stack */
    _fiq_stack_end = ADDR(.fiq_stack) + SIZEOF(.fiq_stack);

    .fiq_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . = . + (4K);
    } >ram

    _ocram_start = ADDR(.ocram);

    .ocram (NOLOAD) :
    {
        . = . + (128K);
    } >ocram

    _gic_start = ADDR(.gic);

    .gic (NOLOAD) :
    {
        . = . + (32K);
    } >gic

    _uart_start = ADDR(.uart);

    .uart (NOLOAD) :
    {
        . = . + (4K);
    } >uart

    _gpt1_start = ADDR(.gpt1);

    .gpt1 (NOLOAD) :
    {
        . = . + (4K);
    } >gpt1

    _gpt2_start = ADDR(.gpt2);

    .gpt2 (NOLOAD) :
    {
        . = . + (4K);
    } >gpt2

    _gpio1_start = ADDR(.gpio1);

    .gpio1 (NOLOAD) :
    {
        . = . + (4K);
    } >gpio1

    _gpio2_start = ADDR(.gpio2);

    .gpio2 (NOLOAD) :
    {
        . = . + (4K);
    } >gpio2

    _gpio3_start = ADDR(.gpio3);

    .gpio3 (NOLOAD) :
    {
        . = . + (4K);
    } >gpio3

    _gpio4_start = ADDR(.gpio4);

    .gpio4 (NOLOAD) :
    {
        . = . + (4K);
    } >gpio4

    _gpio5_start = ADDR(.gpio5);

    .gpio5 (NOLOAD) :
    {
        . = . + (4K);
    } >gpio5

    _ccm_start = ADDR(.ccm);

    .ccm (NOLOAD) :
    {
        . = . + (4K);
    } >ccm

    _analog_start = ADDR(.analog);

    .analog (NOLOAD) :
    {
        . = . + (4K);
    } >analog

    _iomux_start = ADDR(.iomux);

    .iomux (NOLOAD) :
    {
        . = . + (16K);
    } >iomux

    _iomux_gpr_start = ADDR(.iomux_g);

    .iomux_g (NOLOAD) :
    {
        . = . + (16K);
    } >iomux_g

    _enet1_start = ADDR(.enet1);

    .enet1 (NOLOAD) :
    {
        . = . + (4K);
    } >enet1

    _enet2_start = ADDR(.enet2);

    .enet2 (NOLOAD) :
    {
        . = . + (4K);
    } >enet2

    _nvram_start = ADDR(.nvram);

    .nvram (NOLOAD) :
    {
        . = . + (128K);
    } >nvram
}
