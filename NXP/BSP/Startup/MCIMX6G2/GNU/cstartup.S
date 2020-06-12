
/********************************************************************************************************
 *				    EXCEPTION VECTORS & STARTUP CODE
 *
 * File      : cstartup.s
 * For       : Cortex-A7 on the Freescale MCIMX6G
 * Toolchain : GNU
 ********************************************************************************************************/


/********************************************************************************************************
 * 					   MACROS AND DEFINIITIONS
 ********************************************************************************************************/

#define CPSR_MODE_USER                                  0x00000010
#define CPSR_MODE_FIQ                                   0x00000011
#define CPSR_MODE_IRQ                                   0x00000012
#define CPSR_MODE_SUPERVISOR                            0x00000013
#define CPSR_MODE_MONITOR                               0x00000016
#define CPSR_MODE_ABORT                                 0x00000017
#define CPSR_MODE_UNDEFINED                             0x0000001b
#define CPSR_MODE_SYSTEM                                0x0000001f

#define CPSR_FIQ_DISABLED                               (1 << 6)
#define CPSR_IRQ_DISABLED                               (1 << 7)

	/* Exception vector start. */
	.section .entry, "ax", %progbits
	.globl _start_vect
	.globl _start
_start_vect:
_start:
	ldr	pc, __reset
	ldr	pc, __undefined_instruction
	ldr	pc, __software_interrupt
	ldr	pc, __prefetch_abort
	ldr	pc, __data_abort
	ldr	pc, __not_used
	ldr	pc, __irq
	ldr	pc, __fiq
__reset:
	.word _reset
__undefined_instruction:
	.word OS_CPU_ARM_ExceptUndefInstrHndlr
__software_interrupt:
	.word OS_CPU_ARM_ExceptSwiHndlr
__prefetch_abort:
	.word OS_CPU_ARM_ExceptPrefetchAbortHndlr
__data_abort:
	.word OS_CPU_ARM_ExceptDataAbortHndlr
__not_used:
	.word 0
__irq:
	.word OS_CPU_ARM_ExceptIrqHndlr
__fiq:
	.word OS_CPU_ARM_ExceptFiqHndlr
	.global _end_vect
_end_vect:
	/* We should never reach here */
	b	.

	/* Exception stacks */
__svc_stack_end:
	.word _svc_stack_end
__und_stack_end:
	.word _und_stack_end
__abt_stack_end:
	.word _abt_stack_end
__irq_stack_end:
	.word _irq_stack_end
__fiq_stack_end:
	.word _fiq_stack_end
__start_vect:
	.word _start_vect

	/* bss adresses */
__bss_start:
    .word _bss_start
__bss_end:
    .word _bss_end

	.globl _reset
_reset:

/********************************************************************************************************
 *				    STACK POINTER INITIALIZATION
 ********************************************************************************************************/

	/* Disable IRQ & FIQ */
	cpsid	if

	/* load supervisor stack */
	cps	#CPSR_MODE_SUPERVISOR
	ldr	sp, __svc_stack_end

	/* load undefined instruction exception stack */
	cps	#CPSR_MODE_UNDEFINED
	ldr	sp, __und_stack_end

	/* load data abort exception stack */
	cps	#CPSR_MODE_ABORT
	ldr	sp, __abt_stack_end

	/* load interrupt stack */
	cps	#CPSR_MODE_IRQ
	ldr	sp, __irq_stack_end

	/* load FIQ stack */
	cps	#CPSR_MODE_FIQ
	ldr	sp, __fiq_stack_end

	/* get back to supervisor mode (default) */
	cps	#CPSR_MODE_SUPERVISOR

	/* Set exception vector base (VBAR) address */
	ldr	r0, __start_vect
	mcr	p15, 0, r0, c12, c0, 0

	/* Zero-out bss section */
	mov	r0, #0
	ldr	r1, __bss_start
	ldr	r2, __bss_end

_bss_zero:
	str	r0, [r1], #4
	cmp	r1, r2
	blt	_bss_zero

	/* Jump to main */
	b	main
	/* We should never reach here */
	b	.
