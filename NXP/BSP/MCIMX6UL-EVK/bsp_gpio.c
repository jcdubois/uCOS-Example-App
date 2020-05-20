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
* Filename : bsp_gpio.c
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  "bsp_gpio.h"


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
*                                            BSP_GPIO_SetDir()
*
* Description : Set the direction of a GPIO pin.
*
* Argument(s) : base    The base address of the GPIO block.
*
*               pin     The GPIO pin number.
*
*               dir     Either BSP_GPIO_DIR_IN or BSP_GPIO_DIR_OUT
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_GPIO_SetDir (CPU_ADDR    base,
                       CPU_INT08U  pin,
                       CPU_INT08U  dir)
{
    BSP_GPIO_MAP  *p_gpio;


    p_gpio = (BSP_GPIO_MAP *)base;

    if (dir) {
        DEF_BIT_SET(p_gpio->Dir, (1u << pin));                /* Set the direction bit.                                 */
    } else {
        DEF_BIT_CLR(p_gpio->Dir, (1u << pin));                /* Clr the direction bit.                                 */
    }
}


/*
*********************************************************************************************************
*                                              BSP_GPIO_Wr()
*
* Description : Sets the output of a GPIO pin to 1 (HIGH) or 0 (LOW).
*
* Argument(s) : base    The base address of the GPIO block.
*
*               pin     The GPIO pin number.
*
*               val     Either BSP_GPIO_HIGH or BSP_GPIO_LOW.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_GPIO_Wr (CPU_ADDR    base,
                   CPU_INT08U  pin,
                   CPU_INT08U  val)
{
    BSP_GPIO_MAP  *p_gpio;


    p_gpio = (BSP_GPIO_MAP *)base;

    if (val) {
        DEF_BIT_SET(p_gpio->Data, (1u << pin));               /* Set the output to 1 (HIGH).                            */
    } else {
        DEF_BIT_CLR(p_gpio->Data, (1u << pin));               /* Set the output to 0 (LOW).                             */
    }
}
