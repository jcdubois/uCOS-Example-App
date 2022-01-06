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

    /* User stack */
    .user_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . += (4K);
	PROVIDE(_user_stack_end = .);
    } >ram

    /* Supervisor stack */
    .svc_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . += (4K);
	PROVIDE(_svc_stack_end = .);
    } >ram

    /* Abort stack */
    .abt_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . += (4K);
	PROVIDE(_abt_stack_end = .);
    } >ram

    /* Undefined stack */
    .und_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . += (4K);
	PROVIDE(_und_stack_end = .);
    } >ram

    /* IRQ stack */
    .irq_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . += (4K);
	PROVIDE(_irq_stack_end = .);
    } >ram

    /* FIQ stack */
    .fiq_stack (ALIGN(4K) + (4K)) (NOLOAD) :
    {
        . += (4K);
	PROVIDE(_fiq_stack_end = .);
    } >ram

    /* unintialized read/write data section */

    .bss (ALIGN(100M)) (NOLOAD) :
    {
        PROVIDE(_bss_start = .);
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        PROVIDE(_bss_end = .);
    } >ram

    .ocram (NOLOAD) :
    {
        PROVIDE(_ocram_start = .);
        . += (128K);
    } >ocram

    .gic (NOLOAD) :
    {
        PROVIDE(_gic_start = .);
        . += (32K);
    } >gic

    .uart (NOLOAD) :
    {
        PROVIDE(_uart_start = .);
        . += (4K);
    } >uart

    .gpt1 (NOLOAD) :
    {
        PROVIDE(_gpt1_start = .);
        . += (4K);
    } >gpt1

    .gpt2 (NOLOAD) :
    {
        PROVIDE(_gpt2_start = .);
        . += (4K);
    } >gpt2

    .gpio1 (NOLOAD) :
    {
        PROVIDE(_gpio1_start = .);
        . += (4K);
    } >gpio1

    .gpio2 (NOLOAD) :
    {
        PROVIDE(_gpio2_start = .);
        . += (4K);
    } >gpio2

    .gpio3 (NOLOAD) :
    {
        PROVIDE(_gpio3_start = .);
        . += (4K);
    } >gpio3

    .gpio4 (NOLOAD) :
    {
        PROVIDE(_gpio4_start = .);
        . += (4K);
    } >gpio4

    .gpio5 (NOLOAD) :
    {
        PROVIDE(_gpio5_start = .);
        . += (4K);
    } >gpio5

    .ccm (NOLOAD) :
    {
        PROVIDE(_ccm_start = .);
        . += (4K);
    } >ccm

    .analog (NOLOAD) :
    {
        PROVIDE(_analog_start = .);
        . += (4K);
    } >analog

    .iomux (NOLOAD) :
    {
        PROVIDE(_iomux_start = .);
        . += (16K);
    } >iomux

    .iomux_g (NOLOAD) :
    {
        PROVIDE(_iomux_gpr_start = .);
        . += (16K);
    } >iomux_g

    .enet1 (NOLOAD) :
    {
        PROVIDE(_enet1_start = .);
        . += (4K);
    } >enet1

    .enet2 (NOLOAD) :
    {
        PROVIDE(_enet2_start = .);
        . += (4K);
    } >enet2

    .nvram (NOLOAD) :
    {
        PROVIDE(_nvram_start = .);
        . += (128K);
    } >nvram
}
