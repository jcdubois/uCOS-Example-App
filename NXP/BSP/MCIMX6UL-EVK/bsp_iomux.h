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
* Filename : bsp_iomux.h
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

#ifndef  BSP_IOMUX_PRESENT                                      /* See Note #1.                                         */
#define  BSP_IOMUX_PRESENT


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

                                                                /* ---------------- IOMUXC RREGISTERS ----------------- */
#define  BSP_IOMUC_BASE_ADDR                             (CPU_INT32U)(0x020E0000u)

#define  BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00            (BSP_IOMUC_BASE_ADDR + 0x005Cu)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01            (BSP_IOMUC_BASE_ADDR + 0x0060u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06            (BSP_IOMUC_BASE_ADDR + 0x0074u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07            (BSP_IOMUC_BASE_ADDR + 0x0078u)

#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_DATA0        (BSP_IOMUC_BASE_ADDR + 0x00C4u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_DATA1        (BSP_IOMUC_BASE_ADDR + 0x00C8u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_EN           (BSP_IOMUC_BASE_ADDR + 0x00CCu)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_ER           (BSP_IOMUC_BASE_ADDR + 0x00E0u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK          (BSP_IOMUC_BASE_ADDR + 0x00DCu)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_DATA0        (BSP_IOMUC_BASE_ADDR + 0x00D0u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_DATA1        (BSP_IOMUC_BASE_ADDR + 0x00D4u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_EN           (BSP_IOMUC_BASE_ADDR + 0x00D8u)

#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_DATA0        (BSP_IOMUC_BASE_ADDR + 0x00E4u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_DATA1        (BSP_IOMUC_BASE_ADDR + 0x00E8u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_EN           (BSP_IOMUC_BASE_ADDR + 0x00ECu)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_ER           (BSP_IOMUC_BASE_ADDR + 0x0100u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_CLK          (BSP_IOMUC_BASE_ADDR + 0x00FCu)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_DATA0        (BSP_IOMUC_BASE_ADDR + 0x00F0u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_DATA1        (BSP_IOMUC_BASE_ADDR + 0x00F4u)
#define  BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_EN           (BSP_IOMUC_BASE_ADDR + 0x00F8u)

#define  BSP_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00            (BSP_IOMUC_BASE_ADDR + 0x02E8u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01            (BSP_IOMUC_BASE_ADDR + 0x02ECu)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06            (BSP_IOMUC_BASE_ADDR + 0x0300u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07            (BSP_IOMUC_BASE_ADDR + 0x0304u)
                                                                /* Pad Control Registers.                               */
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_RX_DATA0        (BSP_IOMUC_BASE_ADDR + 0x0350u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_RX_DATA1        (BSP_IOMUC_BASE_ADDR + 0x0354u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_RX_EN           (BSP_IOMUC_BASE_ADDR + 0x0358u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_RX_ER           (BSP_IOMUC_BASE_ADDR + 0x036Cu)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_TX_DATA0        (BSP_IOMUC_BASE_ADDR + 0x035Cu)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_TX_DATA1        (BSP_IOMUC_BASE_ADDR + 0x0360u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_TX_EN           (BSP_IOMUC_BASE_ADDR + 0x0364u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_TX_CLK          (BSP_IOMUC_BASE_ADDR + 0x0368u)

#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_RX_DATA0        (BSP_IOMUC_BASE_ADDR + 0x0370u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_RX_DATA1        (BSP_IOMUC_BASE_ADDR + 0x0374u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_RX_EN           (BSP_IOMUC_BASE_ADDR + 0x0378u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_RX_ER           (BSP_IOMUC_BASE_ADDR + 0x038Cu)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_TX_DATA0        (BSP_IOMUC_BASE_ADDR + 0x037Cu)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_TX_DATA1        (BSP_IOMUC_BASE_ADDR + 0x0380u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_TX_EN           (BSP_IOMUC_BASE_ADDR + 0x0384u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_TX_CLK          (BSP_IOMUC_BASE_ADDR + 0x0388u)

                                                                /* Select Input Registers.                              */
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_REF_CLK1        (BSP_IOMUC_BASE_ADDR + 0x0574u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_MAC0_MDIO_SEL   (BSP_IOMUC_BASE_ADDR + 0x0578u)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_REF_CLK2        (BSP_IOMUC_BASE_ADDR + 0x057Cu)
#define  BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_MAC0_MDIO_SEL   (BSP_IOMUC_BASE_ADDR + 0x0580u)

                                                                /* Alternate Mux Mode Definitions.                      */
#define  BSP_IOMUX_ALT_0                                 0x00
#define  BSP_IOMUX_ALT_1                                 0x01
#define  BSP_IOMUX_ALT_2                                 0x02
#define  BSP_IOMUX_ALT_3                                 0x03
#define  BSP_IOMUX_ALT_4                                 0x04
#define  BSP_IOMUX_ALT_5                                 0x05
#define  BSP_IOMUX_ALT_6                                 0x06
#define  BSP_IOMUX_ALT_7                                 0x07
#define  BSP_IOMUX_ALT_8                                 0x08
                                                                /* Software Input On Field (Loopback) Settings.         */
#define  BSP_IOMUX_LOOPBACK_EN                           1u
#define  BSP_IOMUX_LOOPBACK_DIS                          0u

                                                                /* General Purpose Registers.                           */
#define  BSP_IOMUX_GPR1                                 *(CPU_REG32 *)0x020E4004

                                                                /* General Purpose Register settings.                   */
#define  BSP_IOMUX_ENET1_CLK_SEL                         DEF_BIT_13
#define  BSP_IOMUX_ENET1_TX_CLK_DIR                      DEF_BIT_17
#define  BSP_IOMUX_ENET2_CLK_SEL                         DEF_BIT_14
#define  BSP_IOMUX_ENET2_TX_CLK_DIR                      DEF_BIT_18

                                                                /* Pad Control Register Settings.                       */
#define  BSP_IOMUX_PAD_CTL_PAD_HYS(x)                   ((x) << 16u)
#define  BSP_IOMUX_PAD_CTL_PAD_PUS(x)                   ((x) << 14u)
#define  BSP_IOMUX_PAD_CTL_PAD_PUE(x)                   ((x) << 13u)
#define  BSP_IOMUX_PAD_CTL_PAD_PKE(x)                   ((x) << 12u)
#define  BSP_IOMUX_PAD_CTL_PAD_ODE(x)                   ((x) << 11u)
#define  BSP_IOMUX_PAD_CTL_PAD_SPEED(x)                 ((x) <<  6u)
#define  BSP_IOMUX_PAD_CTL_PAD_DSE(x)                   ((x) <<  3u)
#define  BSP_IOMUX_PAD_CTL_PAD_SRE(x)                   ((x) <<  0u)

#define  BSP_IOMUX_HYS_EN                               1u
#define  BSP_IOMUX_HYS_DIS                              0u
#define  BSP_IOMUX_PUS_100K_OHM_PD                      0u
#define  BSP_IOMUX_PUS_47K_OHM_PU                       1u
#define  BSP_IOMUX_PUS_100K_OHM_PU                      2u
#define  BSP_IOMUX_PUS_22K_OHM_PU                       3u
#define  BSP_IOMUX_PUE_KEEP                             0u
#define  BSP_IOMUX_PUE_PULL                             1u
#define  BSP_IOMUX_PKE_EN                               1u
#define  BSP_IOMUX_PKE_DIS                              0u
#define  BSP_IOMUX_ODE_EN                               1u
#define  BSP_IOMUX_ODE_DIS                              0u
#define  BSP_IOMUX_SPEED_50MHZ                          1u
#define  BSP_IOMUX_SPEED_100MHZ                         2u
#define  BSP_IOMUX_SPEED_200MHZ                         3u
#define  BSP_IOMUX_DSE_HIZ                              0u
#define  BSP_IOMUX_DSE_240_OHM                          1u
#define  BSP_IOMUX_DSE_120_OHM                          2u
#define  BSP_IOMUX_DSE_80_OHM                           3u
#define  BSP_IOMUX_DSE_60_OHM                           4u
#define  BSP_IOMUX_DSE_48_OHM                           5u
#define  BSP_IOMUX_DSE_40_OHM                           6u
#define  BSP_IOMUX_DSE_34_OHM                           7u
#define  BSP_IOMUX_SRE_SLOW                             0u
#define  BSP_IOMUX_SRE_FAST                             1u



                                                                /* Select Input Settings.                               */
#define  BSP_IOMUX_ENET1_TX_CLK_ALT4                    2u
#define  BSP_IOMUX_ENET2_TX_CLK_ALT4                    2u
#define  BSP_IOMUX_GPIO1_IO06_ALT0                      0u
#define  BSP_IOMUX_GPIO1_IO06_ALT1                      0u

#define  BSP_IOMUX_SEL_INPUT_MASK                       0x03
#define  BSP_IOMUX_SION_MASK                            0x10
#define  BSP_IOMUX_MUX_MODE_MASK                        0x0F


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


void  BSP_IOMUX_SetMuxMode      (CPU_ADDR  reg, CPU_INT08U  mode);

void  BSP_IOMUX_SetCtlReg       (CPU_ADDR  reg, CPU_INT32U  cfg);

void  BSP_IOMUX_SelInput        (CPU_ADDR  reg, CPU_INT08U  daisy);

void  BSP_IOMUX_SetLoopback     (CPU_ADDR  reg, CPU_INT08U  sion);


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
