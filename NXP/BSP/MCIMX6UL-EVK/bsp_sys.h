/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                            NXP MCIMX6UL
*                                               on the
*
*                                       i.MX6 UltraLite EVK Board
*
* Filename : bsp_sys.h
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This BSP header file is protected from multiple pre-processor inclusion through
*               use of the BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_SYS_PRESENT                                        /* See Note #1.                                         */
#define  BSP_SYS_PRESENT


/*
*********************************************************************************************************
*                                     EXTERNAL C LANGUAGE LINKAGE
*
* Note(s) : (1) C++ compilers MUST 'extern'ally declare ALL C function prototypes & variable/object
*               declarations for correct C language linkage.
*********************************************************************************************************
*/

#ifdef __cplusplus
extern  "C" {                                                   /* See Note #1.                                         */
#endif


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_SYS_MODULE
#define  BSP_SYS_EXT
#else
#define  BSP_SYS_EXT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  GPTIM_PRESCALE                                     24
#define  BSP_CFG_SYS_XTAL_OSC_FREQ_HZ                 24000000u
#define  GPTIM_LOAD                                  (BSP_CFG_SYS_XTAL_OSC_FREQ_HZ / GPTIM_PRESCALE / OS_CFG_TICK_RATE_HZ)

/*
*********************************************************************************************************
*                                             REGISTERS
*********************************************************************************************************
*/

extern volatile char _ccm_start;

#define  BSP_CCM_BASE_ADDR                           (CPU_INT32U)(&_ccm_start)
#define  BSP_REG_CCM_CACRR                           (BSP_CCM_BASE_ADDR + 0x0010u)
#define  BSP_REG_CCM_CCGR1                           (BSP_CCM_BASE_ADDR + 0x006Cu)

extern volatile char _analog_start;

#define  BSP_CCM_ANALOG_BASE_ADDR                  (CPU_INT32U)(&_analog_start)
#define  BSP_REG_CCM_ANALOG_PLL_ARM                  (BSP_CCM_ANALOG_BASE_ADDR + 0x0000u)
#define  BSP_REG_CCM_ANALOG_PLL_SYS                  (BSP_CCM_ANALOG_BASE_ADDR + 0x0030u)


extern volatile char _gic_start;

#define  BSP_SYS_ARM_MP_BASE_ADDR                    (CPU_INT32U)(&_gic_start)

extern volatile char _gpt1_start;

#define  BSP_SYS_GPT1_BASE_ADDR                      (CPU_INT32U)(&_gpt1_start)
#define  BSP_REG_GPT1_CR                             (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x0000u)))
#define  BSP_REG_GPT1_PR                             (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x0004u)))
#define  BSP_REG_GPT1_SR                             (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x0008u)))
#define  BSP_REG_GPT1_IR                             (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x000Cu)))
#define  BSP_REG_GPT1_OCR1                           (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x0010u)))
#define  BSP_REG_GPT1_OCR2                           (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x0014u)))
#define  BSP_REG_GPT1_OCR3                           (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x0018u)))
#define  BSP_REG_GPT1_ICR1                           (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x001Cu)))
#define  BSP_REG_GPT1_ICR2                           (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x0020u)))
#define  BSP_REG_GPT1_CNT                            (*((CPU_REG32 *)(BSP_SYS_GPT1_BASE_ADDR + 0x0024u)))

extern volatile char _gpt2_start;

#define  BSP_SYS_GPT2_BASE_ADDR                      (CPU_INT32U)(&_gpt2_start)
#define  BSP_REG_GPT2_CR                             (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x0000u)))
#define  BSP_REG_GPT2_PR                             (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x0004u)))
#define  BSP_REG_GPT2_SR                             (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x0008u)))
#define  BSP_REG_GPT2_IR                             (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x000Cu)))
#define  BSP_REG_GPT2_OCR1                           (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x0010u)))
#define  BSP_REG_GPT2_OCR2                           (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x0014u)))
#define  BSP_REG_GPT2_OCR3                           (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x0018u)))
#define  BSP_REG_GPT2_ICR1                           (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x001Cu)))
#define  BSP_REG_GPT2_ICR2                           (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x0020u)))
#define  BSP_REG_GPT2_CNT                            (*((CPU_REG32 *)(BSP_SYS_GPT2_BASE_ADDR + 0x0024u)))


/*
*********************************************************************************************************
*                                            REGISTER BITS
*********************************************************************************************************
*/
                                                                /* General Purpose Timers' Control Register.            */
#define  BSP_GPT_CR_EN                               DEF_BIT_00
#define  BSP_GPT_CR_ENMOD                            DEF_BIT_01
#define  BSP_GPT_CR_DBGEN                            DEF_BIT_02
#define  BSP_GPT_CR_WAITEN                           DEF_BIT_03
#define  BSP_GPT_CR_DOZEEN                           DEF_BIT_04
#define  BSP_GPT_CR_STOPEN                           DEF_BIT_05
#define  BSP_GPT_CR_CLKSRC                           DEF_BIT_FIELD( 3u,  6u)
#define  BSP_GPT_CR_FRR                              DEF_BIT_09
#define  BSP_GPT_CR_EN_24M                           DEF_BIT_10
#define  BSP_GPT_CR_SWR                              DEF_BIT_15
#define  BSP_GPT_CR_IM1                              DEF_BIT_FIELD( 2u, 16u)
#define  BSP_GPT_CR_IM2                              DEF_BIT_FIELD( 2u, 18u)
#define  BSP_GPT_CR_OM1                              DEF_BIT_FIELD( 3u, 20u)
#define  BSP_GPT_CR_OM2                              DEF_BIT_FIELD( 3u, 23u)
#define  BSP_GPT_CR_OM3                              DEF_BIT_FIELD( 3u, 26u)
#define  BSP_GPT_CR_FO1                              DEF_BIT_29
#define  BSP_GPT_CR_FO2                              DEF_BIT_30
#define  BSP_GPT_CR_FO3                              DEF_BIT_31
                                                                /* General Purpose Timers' Prescaler Register.          */
#define  BSP_GPT_PR_PRESCALER                        DEF_BIT_FIELD(12u,  0u)
#define  BSP_GPT_PR_PRESCALER24M                     DEF_BIT_FIELD( 4u, 12u)

                                                                /* General Purpose Timers' Status Register.             */
#define  BSP_GPT_SR_OF1                              DEF_BIT_00
#define  BSP_GPT_SR_OF2                              DEF_BIT_01
#define  BSP_GPT_SR_OF3                              DEF_BIT_02
#define  BSP_GPT_SR_IF1                              DEF_BIT_03
#define  BSP_GPT_SR_IF2                              DEF_BIT_04
#define  BSP_GPT_SR_ROV                              DEF_BIT_05
                                                                /* General Purpose Timers' Interrupt Register.          */
#define  BSP_GPT_IR_OF1IE                            DEF_BIT_00
#define  BSP_GPT_IR_OF2IE                            DEF_BIT_01
#define  BSP_GPT_IR_OF3IE                            DEF_BIT_02
#define  BSP_GPT_IR_IF1IE                            DEF_BIT_03
#define  BSP_GPT_IR_IF2IE                            DEF_BIT_04
#define  BSP_GPT_IR_ROVIE                            DEF_BIT_05
                                                                 /* General Purpose Timers' Output Compare Register 1.  */
#define  BSP_GPT_OCR1_COMP                           DEF_BIT_FIELD(32u,  0u)


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void        BSP_LowLevelInit (void);
void        BSP_SysInit      (void);
CPU_INT32U  BSP_SysClkFreqGet(void);
CPU_INT32U  BSP_PerClkFreqGet(void);


/*
*********************************************************************************************************
*                                   EXTERNAL C LANGUAGE LINKAGE END
*********************************************************************************************************
*/

#ifdef __cplusplus
}                                                               /* End of 'extern'al C lang linkage.                    */
#endif


/*
*********************************************************************************************************
*                                               MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
