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
* Filename : bsp_sys.c
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <lib_def.h>
#include  "bsp_ccm.h"
#include  "bsp_sys.h"


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



/*
*********************************************************************************************************
*********************************************************************************************************
**                                        GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         BSP_LowLevelInit()
*
* Description : Board Support Package Low Level Initialization.
*
* Argument(s) : None.
*
* Returns(s)  : None
*
* Caller(s)   : None.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_LowLevelInit (void)
{
}


/*
*********************************************************************************************************
*                                         BSP SYSTEM INITIALIZATION
*
* Description: This function should be called early in the BSP initialization process.
*
* Argument(s): None.
*
* Return(s)  : None.
*
* Caller(s)  : Application.
*
* Note(s)    : 1) When changing  the frequency, be sure to set the standby_mode_en bit of the power
*                 control register in the PL310. For details on the register, see CoreLink Level 2
*                 Cache controller L2C-310 Technical Reference Manual issued by ARM Ltd.
*********************************************************************************************************
*/

void  BSP_SysInit (void)
{
    CPU_BOOLEAN  is_pll_locked;

                                                                /* Enable ARM PLL and configure for 1.05 GHz            */
    BSP_CCM_SetAnalogPLLCtlReg(BSP_REG_CCM_ANALOG_PLL_ARM, 
                              (BSP_CCM_ANALOG_PLL_DIV_SEL(88u) |
                               BSP_CCM_ANALOG_PLL_EN));

    do {
                                                                /* Wait for PLL to lock.                                */
        is_pll_locked = BSP_CCM_IsPLLLocked(BSP_REG_CCM_ANALOG_PLL_ARM);

    } while (is_pll_locked == DEF_NO);
}


/*
*********************************************************************************************************
*                                         SYSTEM CLOCK FREQUENCY
*
* Description: This function is used to retrieve system or CPU clock frequency.
*
* Arguments  : None
*
* Return     : System clock frequency in Hz.
*
* Caller(s)  : Application.
*
* Note(s)    : None
*********************************************************************************************************
*/

CPU_INT32U  BSP_SysClkFreqGet (void)
{
    CPU_INT32U  cpu_freq;
    CPU_INT08U  div_sel;

                                                                /* Get ARM PLL loop divider.                            */
    div_sel  = (BSP_REG_CCM_ANALOG_PLL_ARM & DEF_BIT_FIELD(7u, 0u));
    cpu_freq = ((BSP_CFG_SYS_XTAL_OSC_FREQ_HZ * div_sel) / 2u);
    div_sel  = (BSP_REG_CCM_CACRR & DEF_BIT_FIELD(3u, 0u)) + 1u;
    cpu_freq /= div_sel;

    return (cpu_freq);
}


/*
*********************************************************************************************************
*                                      PERIPHERAL CLOCK FREQUENCY
*
* Description: This function is used to retrieve the private peripheral clock frequency.
*
* Arguments  : None
*
* Return     : Private Peripheral clock frequency in Hz.
*
* Caller(s)  : Application.
*
* Note(s)    : None
*********************************************************************************************************
*/

CPU_INT32U  BSP_PerClkFreqGet (void)
{
    CPU_INT32U  per_freq;


    per_freq = BSP_SysClkFreqGet() / 2;

    return (per_freq);
}
