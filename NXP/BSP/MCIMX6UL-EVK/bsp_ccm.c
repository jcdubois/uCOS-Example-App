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
* Filename : bsp_ccm.c
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  "bsp_ccm.h"


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*********************************************************************************************************
*                                            GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         BSP_CCM_SetClkGateMode()
*
* Description : Sets the mode of a clock gate.
*
* Argument(s) : gate_reg    The address of the clock gate register.
*
*               clk_gate    The clock gate (as a bit-mask) within gate_reg.
*
*               mode        One of the following options :
*                               (1) BSP_CCM_CLK_GATE_MODE_OFF
*                               (2) BSP_CCM_CLK_GATE_MODE_ON_RUN
*                               (3) BSP_CCM_CLK_GATE_MODE_ON
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_CCM_SetClkGateMode (CPU_ADDR    gate_reg,
                              CPU_INT32U  clk_gate,
                              CPU_INT08U  mode)
{
    CPU_REG32  *p_gate_reg;


    p_gate_reg = (CPU_REG32 *)gate_reg;

    DEF_BIT_FIELD_WR(*p_gate_reg, mode, clk_gate);              /* Write mode to the clock gate within the clk gate reg */
}


/*
*********************************************************************************************************
*                                       BSP_CCM_SetAnalogPLLCtlReg()
*
* Description : Configures an analog PLL control register.
*
* Argument(s) : reg
*                   The address of the PLL control register.
*
*               val
*                   The settings to apply to the control register.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_CCM_SetAnalogPLLCtlReg (CPU_ADDR    reg,
                                  CPU_INT32U  val)
{
    CPU_REG32  *p_reg;


    p_reg = (CPU_REG32 *)reg;

   *p_reg = val;
}


/*
*********************************************************************************************************
*                                          BSP_CCM_IsPLLLocked()
*
* Description : Returns true if the LOCK bit is set in the PLL control register (reg).
*
* Argument(s) : reg
*                   The address of the PLL control register.
*
* Return(s)   : DEF_TRUE if the PLL is locked, DEF_FALSE otherwise.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_CCM_IsPLLLocked (CPU_ADDR  reg)
{
    CPU_REG32  *p_reg;


    p_reg = (CPU_REG32 *)reg;

    return ((*p_reg & BSP_CCM_ANALOG_PLL_LOCK) ? DEF_TRUE : DEF_FALSE);
}
