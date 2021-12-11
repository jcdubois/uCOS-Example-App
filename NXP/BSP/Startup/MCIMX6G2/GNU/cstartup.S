
/****************************************************************************
 *                    EXCEPTION VECTORS & STARTUP CODE
 *
 * File      : cstartup.s
 * For       : Cortex-A7 on the Freescale MCIMX6G
 * Toolchain : GNU
 ****************************************************************************/


/****************************************************************************
 *                    MACROS AND DEFINIITIONS
 ****************************************************************************/

#define CPSR_MODE_USER                                  0x00000010
#define CPSR_MODE_FIQ                                   0x00000011
#define CPSR_MODE_IRQ                                   0x00000012
#define CPSR_MODE_SUPERVISOR                            0x00000013
#define CPSR_MODE_MONITOR                               0x00000016
#define CPSR_MODE_ABORT                                 0x00000017
#define CPSR_MODE_UNDEFINED                             0x0000001b
#define CPSR_MODE_SYSTEM                                0x0000001f

    .section .entry, "ax", %progbits
    .globl _start_vect
    .globl _start
_start_vect:
_start:

/****************************************************************************
 *                    Exception Vector Table
 ****************************************************************************/

    ldr pc, __reset
    ldr pc, __undefined_instruction
    ldr pc, __software_interrupt
    ldr pc, __prefetch_abort
    ldr pc, __data_abort
    ldr pc, __not_used
    ldr pc, __irq
    ldr pc, __fiq

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

    /* Exception stacks */
__user_stack_end:
    .word _user_stack_end
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
__gic_start:
    .word _gic_start

    /* bss adresses */
__bss_start:
    .word _bss_start
__bss_end:
    .word _bss_end

    .globl _reset
_reset:

/****************************************************************************
 *                    STACK POINTER INITIALIZATION
 ****************************************************************************/

    cpsid if                        /* Disable IRQ & FIQ */

    ldr r0, __start_vect
    mcr p15, 0, r0, c12, c0, 0      /* Set the exception vector (VBAR) */

    /* MMU, L1$ disable */
    mrc p15, 0, r0, c1, c0, 0       /* Read System Control Register (SCTLR) */
    bic r0, r0, #1                  /* mmu off */
    bic r0, r0, #(1 << 12)          /* i-cache off */
    bic r0, r0, #(1 << 2)           /* d-cache & L2-$ off */
    bic r0, r0, #(1 << 1)           /* disable alignment fault */
    mcr p15, 0, r0, c1, c0, 0       /* Write System Control Register (SCTLR) */

    /* invalidate: L1$, TLB, branch predictor */
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0       /* Invalidate Instruction Cache */
    mcr p15, 0, r0, c7, c5, 6       /* Invalidate branch prediction array */
    mcr p15, 0, r0, c8, c7, 0       /* Invalidate entire Unified Main TLB */
    isb                             /* instr sync barrier */

    /* Enable I cache + branch prediction */
    mrc p15, 0, r0, c1, c0, 0       /* Read System Control Register (SCTLR) */
    mrc p15, 0, r0, c1, c0, 0       /* System control register */
    orr r0, r0, #1 << 12            /* Instruction cache enable */
    orr r0, r0, #1 << 11            /* Program flow prediction */
    mcr p15, 0, r0, c1, c0, 0       /* Write System Control Register (SCTLR) */

    /* load supervisor stack */
    cps #CPSR_MODE_SUPERVISOR
    ldr sp, __svc_stack_end

    /* load undefined instruction exception stack */
    cps #CPSR_MODE_UNDEFINED
    ldr sp, __und_stack_end

    /* load data abort exception stack */
    cps #CPSR_MODE_ABORT
    ldr sp, __abt_stack_end

    /* load interrupt stack */
    cps #CPSR_MODE_IRQ
    ldr sp, __irq_stack_end

    /* load FIQ stack */
    cps #CPSR_MODE_FIQ
    ldr sp, __fiq_stack_end

    /* load SYS stack */
    cps #CPSR_MODE_SYSTEM
    ldr sp, __user_stack_end

/****************************************************************************
 *                    Zero-out bss section
 ****************************************************************************/

    mov r0, #0
    ldr r1, __bss_start
    ldr r2, __bss_end

_bss_zero:
    str r0, [r1], #4
    cmp r1, r2
    blt _bss_zero

/****************************************************************************
 *                    Jump to main
 ****************************************************************************/

    b main
    /* We should never reach here */
    b .
