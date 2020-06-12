OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH("arm")
ENTRY(_start)

SECTIONS
{
	. = 0x80000000;

	. = ALIGN(0x1000);

	.text :
	{
		*(.entry*)
		*(.text*)
	}

	. = ALIGN(0x1000);

	.rodata :
	{
		*(.rodata*);
	}

	. = ALIGN(0x1000);

	.data :
	{
		*(.data*);
	}

	. = ALIGN(0x1000);

	.bss (NOLOAD) :
	{
		PROVIDE(_bss_start = .);
		*(.bss*)
		*(COMMON)
		PROVIDE(_bss_end = .);
	}

	. = ALIGN(0x1000);

	.svc_stack :
	{
		PROVIDE(_svc_stack_start = .);
		. = . + (0x1000);
		. = ALIGN(8);
		PROVIDE(_svc_stack_end = .);
	}

	.abt_stack :
	{
		PROVIDE(_abt_stack_start = .);
		. = . + (0x1000);
		. = ALIGN(8);
		PROVIDE(_abt_stack_end = .);
	}

	.und_stack :
	{
																	PROVIDE(_und_stack_start = .);
		. = . + (0x1000);
		. = ALIGN(8);
		PROVIDE(_und_stack_end = .);
	}

	.irq_stack :
	{
		PROVIDE(_irq_stack_start = .);
		. = . + (0x1000);
		. = ALIGN(8);
		PROVIDE(_irq_stack_end = .);
	}

	.fiq_stack :
	{
		PROVIDE(_fiq_stack_start = .);
		. = . + (0x1000);
		. = ALIGN(8);
		PROVIDE(_fiq_stack_end = .);
	}

	/* End of the read-write data sections */

	. = ALIGN(0x1000);
}
