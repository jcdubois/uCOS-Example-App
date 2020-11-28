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
* Filename : bsp_iomux.c
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  "bsp_iomux.h"


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
*                                          BSP_IOMUX_SetMuxMode()
*
* Description : Sets the MUX_MODE field of a pad mux register.
*
* Argument(s) : reg     The address of the pad mux register.
*
*               mode    The mode to assign to the MUX_MODE field.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IOMUX_SetMuxMode (CPU_ADDR  reg, CPU_INT08U  mode)
{
    CPU_REG32  *p_reg;
    
    
    p_reg  = (CPU_REG32 *)reg;
    
    DEF_BIT_FIELD_WR(*p_reg, mode, BSP_IOMUX_MUX_MODE_MASK);
}


/*
*********************************************************************************************************
*                                        BSP_IOMUX_SetLoopback()
*
* Description : Sets the SION field in the specified mux register.
*
* Argument(s) : reg     The address of the mux register.
*
*               sion    Setting for SION (Loopback) field.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IOMUX_SetLoopback (CPU_ADDR  reg, CPU_INT08U  sion)
{
    CPU_REG32  *p_reg;
    
    
    p_reg = (CPU_REG32 *)reg;
    
    if (sion) {
        DEF_BIT_SET(*p_reg, BSP_IOMUX_SION_MASK);
        
    } else {
        DEF_BIT_CLR(*p_reg, BSP_IOMUX_SION_MASK);
    }
}


/*
*********************************************************************************************************
*                                         BSP_IOMUX_SetCtlReg()
*
* Description : Sets the configuration of a control register.
*
* Argument(s) : reg     The address of the control register.
*
*               cfg     The configuration to assign to the control register.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IOMUX_SetCtlReg (CPU_ADDR  reg, CPU_INT32U  cfg)
{
    CPU_REG32  *p_reg;
    
    
    p_reg = (CPU_REG32 *)reg;
    
   *p_reg = cfg;
}


/*
*********************************************************************************************************
*                                         BSP_IOMUX_SelInput()
*
* Description : Selects the input for the specified input (reg).
*
* Argument(s) : reg     The address of the input select register.
*
*               daisy   Setting for daisy chain input.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IOMUX_SelInput (CPU_ADDR  reg, CPU_INT08U  daisy)
{
    CPU_REG32  *p_reg;
    
    
    p_reg = (CPU_REG32 *)reg;
    
    if (daisy) {
        DEF_BIT_SET(*p_reg, BSP_IOMUX_SEL_INPUT_MASK & daisy);
    } else {
        DEF_BIT_CLR(*p_reg, BSP_IOMUX_SEL_INPUT_MASK);
    }
}
