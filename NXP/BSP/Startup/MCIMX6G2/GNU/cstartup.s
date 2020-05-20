;
;********************************************************************************************************
;                                    EXCEPTION VECTORS & STARTUP CODE
;
; File      : cstartup.s
; For       : Cortex-A7 on the Freescale MCIMX6G
; Toolchain : IAR EWARM V5.10 and higher
;********************************************************************************************************
;

;********************************************************************************************************
;                                           MACROS AND DEFINIITIONS
;********************************************************************************************************

                                                                ; Mode, correspords to bits 0-5 in CPSR
MODE_BITS                  DEFINE   0x1F                        ; Bit mask for mode bits in CPSR
USR_MODE                   DEFINE   0x10                        ; User mode
FIQ_MODE                   DEFINE   0x11                        ; Fast Interrupt Request mode
IRQ_MODE                   DEFINE   0x12                        ; Interrupt Request mode
SVC_MODE                   DEFINE   0x13                        ; Supervisor mode
ABT_MODE                   DEFINE   0x17                        ; Abort mode
UND_MODE                   DEFINE   0x1B                        ; Undefined Instruction mode
SYS_MODE                   DEFINE   0x1F                        ; System mode

                                                                ; Control register C1
CTRL_C1_M                  DEFINE   0x0001
CTRL_C1_A                  DEFINE   0x0002
CTRL_C1_C                  DEFINE   0x0004
CTRL_C1_W                  DEFINE   0x0008
CTRL_C1_S                  DEFINE   0x0100
CTRL_C1_R                  DEFINE   0x0200
CTRL_C1_Z                  DEFINE   0x0800
CTRL_C1_I                  DEFINE   0x1000
CTRL_C1_V                  DEFINE   0x2000
CTRL_C1_RR                 DEFINE   0x4000
CTRL_C1_TRE                DEFINE   0x10000000

                                                                ; Auxiliary control register C1
AUX_C1_FW                  DEFINE   0x0001
AUX_C1_SMP                 DEFINE   0x0040

                                                                ; Level 1 page table descriptor templates
TTB_ENTRY_SUPERSEC_FAULT   DEFINE   0x50006
TTB_ENTRY_SUPERSEC_STRONG  DEFINE   0x50C02
TTB_ENTRY_SUPERSEC_DEV     DEFINE   0x50C06
TTB_ENTRY_SUPERSEC_NORM    DEFINE   0x51C0E

TTB_ENTRY_SEC_STRONG       DEFINE   0x10C02                     ; Normally use for internal memory
TTB_ENTRY_SEC_DEV          DEFINE   0x10C06                     ; Normally use for peripheral space
TTB_ENTRY_SEC_NORM         DEFINE   0x15C06                     ; Normally use for external Memory

;********************************************************************************************************
;                                            ARM EXCEPTION VECTORS
;********************************************************************************************************

    SECTION .intvec:CODE:NOROOT(2)
    PUBLIC  __vector
    PUBLIC  __iar_program_start


    IMPORT  OS_CPU_ARM_ExceptUndefInstrHndlr
    IMPORT  OS_CPU_ARM_ExceptSwiHndlr
    IMPORT  OS_CPU_ARM_ExceptPrefetchAbortHndlr
    IMPORT  OS_CPU_ARM_ExceptDataAbortHndlr
    IMPORT  OS_CPU_ARM_ExceptIrqHndlr
    IMPORT  OS_CPU_ARM_ExceptFiqHndlr

    ARM

__vector:
    LDR     PC, [PC,#24]                                        ; Absolute jump can reach 4 GByte
    LDR     PC, [PC,#24]                                        ; Branch to undef_handler
    LDR     PC, [PC,#24]                                        ; Branch to swi_handler
    LDR     PC, [PC,#24]                                        ; Branch to prefetch_handler
    LDR     PC, [PC,#24]                                        ; Branch to data_handler
__vector_0x14:
    DC32    0                                                   ; Reserved
    LDR     PC, [PC,#24]                                        ; Branch to irq_handler
    LDR     PC, [PC,#24]                                        ; Branch to fiq_handler


    DC32    __iar_program_start
    DC32    OS_CPU_ARM_ExceptUndefInstrHndlr
    DC32    OS_CPU_ARM_ExceptSwiHndlr
    DC32    OS_CPU_ARM_ExceptPrefetchAbortHndlr
    DC32    OS_CPU_ARM_ExceptDataAbortHndlr
    DC32    0
    DC32    OS_CPU_ARM_ExceptIrqHndlr
    DC32    OS_CPU_ARM_ExceptFiqHndlr


;********************************************************************************************************
;                                   LOW-LEVEL INITIALIZATION
;********************************************************************************************************

    SECTION FIQ_STACK:DATA:NOROOT(3)
    SECTION IRQ_STACK:DATA:NOROOT(3)
    SECTION SYS_STACK:DATA:NOROOT(3)
    SECTION ABT_STACK:DATA:NOROOT(3)
    SECTION UND_STACK:DATA:NOROOT(3)
    SECTION CSTACK:DATA:NOROOT(3)
    SECTION MMU_TT:DATA:NOROOT(3)
    SECTION text:CODE:NOROOT(2)
    REQUIRE __vector
    EXTERN  ?main
    PUBLIC  __iar_program_start
    EXTERN  lowlevel_init
    EXTWEAK __iar_init_core
    EXTWEAK __iar_init_vfp

__iar_program_start:

;********************************************************************************************************
;                                    STACK POINTER INITIALIZATION
;********************************************************************************************************

    MRS     r0, cpsr                                            ; Original PSR value

    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#UND_MODE                                     ; Set UND mode bits
    MSR     cpsr_c,r0                                           ; Change the mode
    LDR     sp,=SFE(UND_STACK)                                  ; End of UND_STACK

    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#ABT_MODE                                     ; Set ABT mode bits
    MSR     cpsr_c,r0                                           ; Change the mode
    LDR     sp,=SFE(ABT_STACK)                                  ; End of ABT_STACK

    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#FIQ_MODE                                     ; Set FIQ mode bits
    MSR     cpsr_c,r0                                           ; Change the mode
    LDR     sp,=SFE(FIQ_STACK)                                  ; End of FIQ_STACK

    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#IRQ_MODE                                     ; Set IRQ mode bits
    MSR     cpsr_c,r0                                           ; Change the mode
    LDR     sp,=SFE(IRQ_STACK)                                  ; End of IRQ_STACK

    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#SYS_MODE                                     ; Set System mode bits
    MSR     cpsr_c,r0                                           ; Change the mode
    LDR     sp,=SFE(SYS_STACK)                                  ; End of SYS_STACK

    MRS     r0,cpsr                                             ; Original PSR value
    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#SVC_MODE                                     ; Set SVC mode bits
    MSR     cpsr_c,r0                                           ; Change the mode
    LDR     sp,=SFE(CSTACK)                                     ; End of SVC_STACK

    ;; Turn on core features assumed to be enabled.
      FUNCALL __iar_program_start, __iar_init_core
    BL      __iar_init_core
   
    ;; Initialize VFP (if needed).
      FUNCALL __iar_program_start, __iar_init_vfp
    BL      __iar_init_vfp
;********************************************************************************************************
;                           CONTINUE TO ?main FOR ADDITIONAL INITIALIZATION
;********************************************************************************************************

    LDR     r0,=?main
    BX      r0

    END
