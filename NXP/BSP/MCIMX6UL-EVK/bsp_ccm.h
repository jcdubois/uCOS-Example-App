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
* Filename : bsp_ccm.h
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

#ifndef  BSP_CCM_PRESENT                                       /* See Note #1.                                         */
#define  BSP_CCM_PRESENT


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
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_MODULE
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

                                                                /* Clock gate register addresses.                       */
#define  BSP_CCM_CCGR0                               0x020C4068
#define  BSP_CCM_CCGR1                               0x020C406C
#define  BSP_CCM_CCGR2                               0x020C4070
#define  BSP_CCM_CCGR3                               0x020C4074
#define  BSP_CCM_CCGR4                               0x020C4078
#define  BSP_CCM_CCGR5                               0x020C407C
#define  BSP_CCM_CCGR6                               0x020C4080
                                                                /* Clock gate masks. (Bit-fields within CGR.)           */
#define  BSP_CCM_CLK_GATE_00_MASK                    0x00000003
#define  BSP_CCM_CLK_GATE_01_MASK                    0x0000000C
#define  BSP_CCM_CLK_GATE_02_MASK                    0x00000030
#define  BSP_CCM_CLK_GATE_03_MASK                    0x000000C0
#define  BSP_CCM_CLK_GATE_04_MASK                    0x00000300
#define  BSP_CCM_CLK_GATE_05_MASK                    0x00000C00
#define  BSP_CCM_CLK_GATE_06_MASK                    0x00003000
#define  BSP_CCM_CLK_GATE_07_MASK                    0x0000C000
#define  BSP_CCM_CLK_GATE_08_MASK                    0x00030000
#define  BSP_CCM_CLK_GATE_09_MASK                    0x000C0000
#define  BSP_CCM_CLK_GATE_10_MASK                    0x00300000
#define  BSP_CCM_CLK_GATE_11_MASK                    0x00C00000
#define  BSP_CCM_CLK_GATE_12_MASK                    0x03000000
#define  BSP_CCM_CLK_GATE_13_MASK                    0x0C000000
#define  BSP_CCM_CLK_GATE_14_MASK                    0x30000000
#define  BSP_CCM_CLK_GATE_15_MASK                    0xC0000000

                                                                /* Specific clock gates.                                */
#define  BSP_CCM_ENET_CLK_EN                         BSP_CCM_CLK_GATE_02_MASK

                                                                /* Clock gate modes.                                    */
#define  BSP_CCM_CLK_GATE_MODE_OFF                   0u
#define  BSP_CCM_CLK_GATE_MODE_ON_RUN                1u
#define  BSP_CCM_CLK_GATE_MODE_ON                    3u


                                                                /* Analog PLL Register field masks.                     */
#define  BSP_CCM_ANALOG_PLL_DIV_SEL(x)               ((x) <<  0u)
#define  BSP_CCM_ANALOG_PLL_PWR_DOWN                 DEF_BIT_12
#define  BSP_CCM_ANALOG_PLL_EN                       DEF_BIT_13
#define  BSP_CCM_ANALOG_PLL_BYPASS_CLK_SRC(x)        ((x) << 14u)
#define  BSP_CCM_ANALOG_PLL_BYPASS                   DEF_BIT_16
#define  BSP_CCM_ANALOG_PLL_SEL                      DEF_BIT_19
#define  BSP_CCM_ANALOG_PLL_LOCK                     DEF_BIT_31
                                                                /* Analog PLL Registers.                                */
#define  BSP_CCM_ANALOG_PLL_ENET                     0x020C80E0

#define  BSP_CCM_ANALOG_PLL_ENET_DIV_SEL_ENET0(x)    ((x) <<  0u)
#define  BSP_CCM_ANALOG_PLL_ENET_DIV_SEL_ENET1(x)    ((x) <<  2u)
#define  BSP_CCM_ANALOG_PLL_ENET_PWR_DOWN            DEF_BIT_12
#define  BSP_CCM_ANALOG_PLL_ENET1_125M_EN            DEF_BIT_13
#define  BSP_CCM_ANALOG_PLL_ENET_BYPASS_CLK_SRC(x)   ((x) << 14u)
#define  BSP_CCM_ANALOG_PLL_ENET_BYPASS              DEF_BIT_16
#define  BSP_CCM_ANALOG_PLL_ENET_PFD_OFFSET_EN       DEF_BIT_18
#define  BSP_CCM_ANALOG_PLL_ENET_EN_125M             DEF_BIT_19
#define  BSP_CCM_ANALOG_PLL_ENET2_125M_EN            DEF_BIT_20
#define  BSP_CCM_ANALOG_PLL_ENET_25M_REF_EN          DEF_BIT_21
#define  BSP_CCM_ANALOG_PLL_ENET_LOCK                DEF_BIT_31

#define  BSP_CCM_ANALOG_PLL_USB_CLKS                 DEF_BIT_06

#define  BSP_CCM_DIV_SEL_25MHZ                       0x00u
#define  BSP_CCM_DIV_SEL_50MHZ                       0x01u
#define  BSP_CCM_DIV_SEL_100MHZ                      0x02u
#define  BSP_CCM_DIV_SEL_125MHZ                      0x03u


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     REGISTER BIT DEFINITIONS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_CCM_SetClkGateMode    (CPU_ADDR    gate_reg,
                                        CPU_INT32U  clk_gate,
                                        CPU_INT08U  mode);

void         BSP_CCM_SetAnalogPLLCtlReg(CPU_ADDR    reg,
                                        CPU_INT32U  val);

CPU_BOOLEAN  BSP_CCM_IsPLLLocked       (CPU_ADDR    reg);


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
