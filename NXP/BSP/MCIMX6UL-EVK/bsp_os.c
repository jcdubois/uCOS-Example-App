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
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                            NXP MCIMX6UL
*                                               on the
*
*                                       i.MX6 UltraLite EVK Board
*
* Filename : bsp_os.c
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDES
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#define    OS_BSP_MODULE

#include  <os.h>

#include  <cpu_core.h>
#include  "bsp_sys.h"
#include  "bsp_int.h"
#include  "bsp_os.h"

#include  "printf.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_OS_TickISR_Handler(CPU_INT32U  cpu_id);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                     INITIALIZE TICKER INTERRUPT
*
* Description : Initialize the the tick interrupt.
*
* Argument(s) : tick_rate      Number of ticks per second.
*
* Return(s)   : none.
*
* Note(s)     : none
*********************************************************************************************************
*/

void  BSP_OS_TickInit (CPU_INT32U  tick_rate)
{
                                                                /* -              CONFIGURE GPT1 TIMER MODE           - */
    DEF_BIT_SET(BSP_REG_GPT1_CR, BSP_GPT_CR_SWR);
    
    while (BSP_REG_GPT1_CR == BSP_GPT_CR_SWR);
    
    DEF_BIT_CLR(BSP_REG_GPT1_CR, (BSP_GPT_CR_CLKSRC));
                                                                /* Set 24 MHz Crystal as the timer clock source.        */
    DEF_BIT_SET(BSP_REG_GPT1_CR, (BSP_GPT_CR_CLKSRC & 5u << 6u) | 
                                  BSP_GPT_CR_ENMOD              |
                                  BSP_GPT_CR_DBGEN              |
                                  BSP_GPT_CR_WAITEN             |
                                  BSP_GPT_CR_DOZEEN             |
                                  BSP_GPT_CR_STOPEN             |             
                                  BSP_GPT_CR_EN_24M);

    
                                                                /* Set GPT1 Timer Prescalers.                           */
    DEF_BIT_CLR(BSP_REG_GPT1_PR,  BSP_GPT_PR_PRESCALER);
    DEF_BIT_SET(BSP_REG_GPT1_PR, (BSP_GPT_PR_PRESCALER & (GPTIM_PRESCALE - 1u)));
    DEF_BIT_CLR(BSP_REG_GPT1_PR,  BSP_GPT_PR_PRESCALER24M);

                                                                /* Clear Timer Status Register Flags.                   */
    DEF_BIT_SET(BSP_REG_GPT1_SR, (BSP_GPT_SR_OF1   |
                                  BSP_GPT_SR_OF2   |
                                  BSP_GPT_SR_OF3   |
                                  BSP_GPT_SR_IF1   |
                                  BSP_GPT_SR_IF2   |
                                  BSP_GPT_SR_ROV   ));


                                                                /* Set GTPT1 reload value.                              */
    BSP_REG_GPT1_OCR1 = GPTIM_LOAD;

                                                                /* Enable Channel 1 Output Compare int. Ignore the rest.*/
    DEF_BIT_SET(BSP_REG_GPT1_IR,  BSP_GPT_IR_OF1IE);

    DEF_BIT_CLR(BSP_REG_GPT1_IR, (BSP_GPT_IR_OF2IE |
                                  BSP_GPT_IR_OF3IE |
                                  BSP_GPT_IR_IF1IE |
                                  BSP_GPT_IR_IF2IE |
                                  BSP_GPT_IR_ROVIE ));

    BSP_IntVectSet(BSP_INT_SRC_GPT1,                           /* Assign ISR handler.                                   */
                   0u,
                   0u,
                   BSP_OS_TickISR_Handler);

    BSP_IntSrcEn(BSP_INT_SRC_GPT1);
}


/*
*********************************************************************************************************
*                                         BSP_OS_TickEnable()
*
* Description : Enable the OS tick interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none
*********************************************************************************************************
*/

void  BSP_OS_TickEnable (void)
{
    DEF_BIT_CLR(BSP_REG_GPT1_CR, BSP_GPT_CR_FRR);              /* Configure timer for restart mode.                     */
    DEF_BIT_SET(BSP_REG_GPT1_CR, BSP_GPT_CR_EN);               /* Start the timer.                                      */
}


/*
*********************************************************************************************************
*                                        BSP_OS_TickDisable()
*
* Description : Disable the OS tick interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none
*********************************************************************************************************
*/

void  BSP_OS_TickDisable (void)
{
    DEF_BIT_CLR(BSP_REG_GPT1_CR, BSP_GPT_CR_EN);               /* Disables the GPT timer.                               */
}

/*
*********************************************************************************************************
*                                          ARM INTERRUPT/EXCEPTION HANDLER
*
* Description : Handle ARM exceptions.
*
* Argument(s) : except_id     ARM exception source identifier:
*
*                                  OS_CPU_ARM_EXCEPT_RESET             0x00
*                                  OS_CPU_ARM_EXCEPT_UNDEF_INSTR       0x01
*                                  OS_CPU_ARM_EXCEPT_SWI               0x02
*                                  OS_CPU_ARM_EXCEPT_PREFETCH_ABORT    0x03
*                                  OS_CPU_ARM_EXCEPT_DATA_ABORT        0x04
*                                  OS_CPU_ARM_EXCEPT_ADDR_ABORT        0x05
*                                  OS_CPU_ARM_EXCEPT_IRQ               0x06
*                                  OS_CPU_ARM_EXCEPT_FIQ               0x07
*
* Return(s)   : none.
*
* Note(s)     : (1) Only OS_CPU_ARM_EXCEPT_FIQ and OS_CPU_ARM_EXCEPT_IRQ exceptions handler are implemented.
*                   For the rest of the exception a infinite loop is implemented for debuging pruposes. This behavior
*                   should be replaced with another behavior (reboot, etc).
*********************************************************************************************************
*/

void  OS_CPU_ExceptHndlr (CPU_INT32U  except_id)
{
    switch (except_id) {
        case OS_CPU_ARM_EXCEPT_IRQ:
             BSP_IntHandler();
             break;


        case OS_CPU_ARM_EXCEPT_FIQ:
             BSP_IntHandler();
             break;


        case OS_CPU_ARM_EXCEPT_RESET:
        case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
        case OS_CPU_ARM_EXCEPT_SWI:
        case OS_CPU_ARM_EXCEPT_DATA_ABORT:
        case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
        case OS_CPU_ARM_EXCEPT_ADDR_ABORT:
        default:
             printf("Exception %d\n", except_id);
             while (DEF_TRUE) {                                 /* See Note #1.                                              */
                 ;
             }
             break;
    }
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                 INITIALIZE TICKER INTERRUPT HANDLER
*
* Description: Tick interrupt handler.
*
* Arguments  : 'p_arg'  Pointer to interrupt handler argument.
*
* Return(s)   : None.
*
* Caller(s)   : None.
*
* Note(s)     : None.
*********************************************************************************************************
*/

static void  BSP_OS_TickISR_Handler (CPU_INT32U  cpu_id)
{
    CPU_SR_ALLOC();
    
    CPU_CRITICAL_ENTER();    
    DEF_BIT_SET(BSP_REG_GPT1_SR, BSP_GPT_SR_OF1);               /* Clear Channel 1 Compare Flag in Status Register.     */
    CPU_CRITICAL_EXIT();
    
    OSTimeTick();
}

/*
*********************************************************************************************************
*********************************************************************************************************
**                                      uC/OS-III DYNAMIC TICK
*********************************************************************************************************
*********************************************************************************************************
*/

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)


/*
*********************************************************************************************************
*                                          BSP_OS_TickGet()
*
* Description : Get the OS Tick Counter as if it was running continuously.
*
* Argument(s) : none.
*
* Return(s)   : The effective OS Tick Counter.
*
* Caller(s)   : OS_TaskBlock, OS_TickListInsertDly and OSTimeGet.
*
*               This function is an INTERNAL uC/OS-III function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

OS_TICK  BSP_OS_TickGet (void)
{
    OS_TICK  tick;


#error "BSP_OS_TickGet() needs to be implemented."

    return (tick);
}


/*
*********************************************************************************************************
*                                        BSP_OS_TickNextSet()
*
* Description : Set the number of OS Ticks to wait before calling OSTimeTick.
*
* Argument(s) : ticks       number of OS Ticks to wait.
*
* Return(s)   : Number of effective OS Ticks until next OSTimeTick.
*
* Caller(s)   : OS_TickTask and OS_TickListInsert.
*
*               This function is an INTERNAL uC/OS-III function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

OS_TICK  BSP_OS_TickNextSet (OS_TICK  ticks)
{
    OS_TICK  tick;


#error "BSP_OS_TickNextSet() needs to be implemented."

    return (tick);
}

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of uC/OS-III Dynamic Tick module.                */
