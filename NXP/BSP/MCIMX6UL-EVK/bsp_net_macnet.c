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
*                            NETWORK BOARD SUPPORT PACKAGE (BSP) FUNCTIONS
*
* Filename : bsp_net_macnet.c
* Version  : V3.05.00
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#define    NET_BSP_MODULE
#include  <KAL/kal.h>
#include  <IF/net_if_ether.h>
#include  "bsp_gpio.h"
#include  "bsp_iomux.h"
#include  "bsp_ccm.h"
#include  "bsp_int.h"

#ifdef  NET_IF_ETHER_MODULE_EN


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*********************************************************************************************************
*/

#define  NET_DEV_CLK_FREQ               50000000u


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                  NETWORK DEVICE INTERFACE NUMBERS
*
* Note(s) : (1) Each network device maps to a unique network interface number.
*********************************************************************************************************
*/

static  NET_IF_NBR  IMX6UL_MACNet_1_IF_Nbr = NET_IF_NBR_NONE;
static  NET_IF_NBR  IMX6UL_MACNet_2_IF_Nbr = NET_IF_NBR_NONE;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                               NETWORK DEVICE BSP FUNCTION PROTOTYPES
*********************************************************************************************************
*/

                                                                 /* -- IF #1 : GENERIC ETHER BSP FUNCTION PROTOTYPES -- */
static  void        NetDev_CfgClk            (NET_IF      *p_if,
                                              NET_ERR     *p_err);

static  void        NetDev_CfgIntCtrl_1      (NET_IF      *p_if,
                                              NET_ERR     *p_err);

static  void        NetDev_CfgIntCtrl_2      (NET_IF      *p_if,
                                              NET_ERR     *p_err);

static  void        NetDev_CfgGPIO           (NET_IF      *p_if,
                                              NET_ERR     *p_err);

static  CPU_INT32U  NetDev_ClkFreqGet        (NET_IF      *p_if,
                                              NET_ERR     *p_err);

        void        NetDev_MACNetISR_Handler1(CPU_INT32U   id);
        
        void        NetDev_MACNetISR_Handler2(CPU_INT32U   id);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    NETWORK DEVICE BSP INTERFACE
*********************************************************************************************************
*/

const  NET_DEV_BSP_ETHER  NetDev_BSP_MACNet_1 = {                              /* Board-/device-specific BSP fnct ptrs: */
                                                  &NetDev_CfgClk,              /*   Cfg clk(s)                          */
                                                  &NetDev_CfgIntCtrl_1,        /*   Cfg int ctrl(s)                     */
                                                  &NetDev_CfgGPIO,             /*   Cfg GPIO                            */
                                                  &NetDev_ClkFreqGet           /*   Get clk freq                        */
                                                };

const  NET_DEV_BSP_ETHER  NetDev_BSP_MACNet_2 = {                              /* Board-/device-specific BSP fnct ptrs: */
                                                  &NetDev_CfgClk,              /*   Cfg clk(s)                          */
                                                  &NetDev_CfgIntCtrl_2,        /*   Cfg int ctrl(s)                     */
                                                  &NetDev_CfgGPIO,             /*   Cfg GPIO                            */
                                                  &NetDev_ClkFreqGet           /*   Get clk freq                        */
                                                };


/*
*********************************************************************************************************
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                              NETWORK ETHERNET DEVICE DRIVER FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           NetDev_CfgClk()
*
* Description : Configure clocks for the specified interface/device.
*
* Argument(s) : p_if         Pointer to network interface to configure.
*               ----         Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device clock(s)     successfully configured.
*                               NET_DEV_ERR_FAULT               Device clock(s) NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : NetDev_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  NetDev_CfgClk (NET_IF   *p_if,
                             NET_ERR  *p_err)
{
    CPU_BOOLEAN  is_pll_locked;


   (void)p_if;                                                 /* Prevent 'variable unused' compiler warning.          */
    is_pll_locked = BSP_CCM_IsPLLLocked(BSP_CCM_ANALOG_PLL_ENET);
    
    if (is_pll_locked == DEF_TRUE) {                            /* Don't re-config Clk if either IF initialized it first*/
       *p_err = NET_DEV_ERR_NONE;
        return;     
    }
      
    BSP_CCM_SetClkGateMode(BSP_CCM_CCGR3,                       /* Gate Register 3.                                     */
                           BSP_CCM_ENET_CLK_EN,                 /* Gate : enet_clk_en.                                  */
                           BSP_CCM_CLK_GATE_MODE_ON);

                                                                /* Enable ENET_REF_CLK PLL.                             */
    BSP_CCM_SetAnalogPLLCtlReg(BSP_CCM_ANALOG_PLL_ENET, 
                               BSP_CCM_ANALOG_PLL_ENET1_125M_EN                             |
                               BSP_CCM_ANALOG_PLL_ENET2_125M_EN                             |
                               BSP_CCM_ANALOG_PLL_ENET_DIV_SEL_ENET0(BSP_CCM_DIV_SEL_50MHZ) |
                               BSP_CCM_ANALOG_PLL_ENET_DIV_SEL_ENET1(BSP_CCM_DIV_SEL_50MHZ) );

                                                                /* Wait for PLL to lock.                                */                               
    do {
        is_pll_locked = BSP_CCM_IsPLLLocked(BSP_CCM_ANALOG_PLL_ENET);
    } while (is_pll_locked == DEF_NO);

   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                         NetDev_CfgIntCtrl_1()
*
* Description : Configure interrupts &/or interrupt controller for the specified interface/device.
*
* Argument(s) : p_if         Pointer to network interface to configure.
*               ----         Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device interrupt(s)     successfully configured.
*                               NET_DEV_ERR_FAULT               Device interrupt(s) NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : NetDev_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  NetDev_CfgIntCtrl_1 (NET_IF   *p_if,
                                   NET_ERR  *p_err)
{
    CPU_BOOLEAN  is_set;


    IMX6UL_MACNet_1_IF_Nbr = p_if->Nbr;                         /* Cfg MacNet's ENET1 instance w/ specific IF number.   */
    is_set                 = BSP_IntVectSet(BSP_INT_SRC_ENET1,
                                            0u,
                                            DEF_BIT_00,
                                            NetDev_MACNetISR_Handler1);

    BSP_IntSrcEn(BSP_INT_SRC_ENET1);

   *p_err = (is_set) ? NET_DEV_ERR_NONE : NET_DEV_ERR_FAULT;
}


/*
*********************************************************************************************************
*                                         NetDev_CfgIntCtrl_2()
*
* Description : Configure interrupts &/or interrupt controller for the specified interface/device.
*
* Argument(s) : p_if         Pointer to network interface to configure.
*               ----         Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device interrupt(s)     successfully configured.
*                               NET_DEV_ERR_FAULT               Device interrupt(s) NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : NetDev_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  NetDev_CfgIntCtrl_2 (NET_IF   *p_if,
                                   NET_ERR  *p_err)
{
    CPU_BOOLEAN  is_set;


    IMX6UL_MACNet_2_IF_Nbr = p_if->Nbr;                         /* Cfg MacNet's ENET2 instance w/ specific IF number.   */
    is_set                 = BSP_IntVectSet(BSP_INT_SRC_ENET2,
                                            0u,
                                            DEF_BIT_00,
                                            NetDev_MACNetISR_Handler2);
    BSP_IntSrcEn(BSP_INT_SRC_ENET2);

   *p_err = (is_set) ? NET_DEV_ERR_NONE : NET_DEV_ERR_FAULT;
}


/*
*********************************************************************************************************
*                                          NetDev_CfgGPIO()
*
* Description : Configure general-purpose I/O (GPIO) for the specified interface/device.
*
* Argument(s) : p_if         Pointer to network interface to configure.
*               ----         Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device GPIO     successfully configured.
*                               NET_DEV_ERR_FAULT               Device GPIO NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : NetDev_Init().
*
* Note(s)     : (1) When both ENET1 and ENET2 are enabled, ENET1's operation will be momentarily suspended
*                   until ENET2 is finished initializing. This is because the MDIO and MDC signals on both 
*                   interfaces communicate through GPIO6 and GPIO7, respectively. These GPIO's MUX registers
*                   are given the corresponding alternate mux mode values in this function so that the MAC 
*                   can communicate with both PHYs later in the initialization process.
*********************************************************************************************************
*/

static  void  NetDev_CfgGPIO (NET_IF   *p_if,
                              NET_ERR  *p_err)
{
   *p_err = NET_DEV_ERR_NONE;

    if (p_if->Nbr == IMX6UL_MACNet_1_IF_Nbr) {                                 /*     - CONFIGURE GPIO PINS FOR ENET1 INTERFACE      - */
        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_DATA0, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_RX_DATA0,  
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_DATA1, BSP_IOMUX_ALT_0);                                   

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_RX_DATA1,  
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_EN, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_RX_EN,    
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_ER, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_RX_ER,     
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK,   BSP_IOMUX_ALT_4);
        BSP_IOMUX_SelInput   (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_REF_CLK1, BSP_IOMUX_ENET1_TX_CLK_ALT4);
        BSP_IOMUX_SetLoopback(BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK,   BSP_IOMUX_LOOPBACK_EN);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_TX_CLK,   
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_40_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_100MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PKE  (BSP_IOMUX_PKE_EN));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_DATA0, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_TX_DATA0, 
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_DATA1, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_TX_DATA1, 
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_EN, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_TX_EN,     
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PKE  (BSP_IOMUX_PKE_EN)        |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00, BSP_IOMUX_ALT_6);

        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01, BSP_IOMUX_ALT_6);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01,      
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_40_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PKE  (BSP_IOMUX_PKE_EN));
                                                                               /* Set GPIO6 & GPIO7 as MDIO and MDC, (See Note 1).     */ 
        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06, BSP_IOMUX_ALT_0);
        BSP_IOMUX_SelInput   (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET1_MAC0_MDIO_SEL, BSP_IOMUX_GPIO1_IO06_ALT0);

        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07, BSP_IOMUX_ALT_0);

        DEF_BIT_SET(BSP_IOMUX_GPR1, BSP_IOMUX_ENET1_TX_CLK_DIR);               /* Set the Tx clock direction for ENET1.                */                                                         
       
    } else if (p_if->Nbr == IMX6UL_MACNet_2_IF_Nbr) {                          /*      - CONFIGURE GPIO PINS FOR ENET2 INTERFACE -     */
        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_DATA0, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_RX_DATA0,  
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_DATA1, BSP_IOMUX_ALT_0);                                   

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_RX_DATA1,  
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_EN, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_RX_EN,
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_ER, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_RX_ER,    
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_CLK,   BSP_IOMUX_ALT_4);
        BSP_IOMUX_SelInput   (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_REF_CLK2, BSP_IOMUX_ENET2_TX_CLK_ALT4);
        BSP_IOMUX_SetLoopback(BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_CLK,   BSP_IOMUX_LOOPBACK_EN);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_TX_CLK,     
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_40_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_100MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PKE  (BSP_IOMUX_PKE_EN));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_DATA0, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_TX_DATA0,  
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_DATA1, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_TX_DATA1,  
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));


        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_EN, BSP_IOMUX_ALT_0);

        BSP_IOMUX_SetCtlReg  (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_TX_EN,
                              BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                              BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                              BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                              BSP_IOMUX_PAD_CTL_PAD_PKE  (BSP_IOMUX_PKE_EN)        |
                              BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                              BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));
                                                                               /* Set GPIO6 & GPIO7 as MDIO and MDC, (See Note 1).     */
        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06, BSP_IOMUX_ALT_1); 
        
        BSP_IOMUX_SelInput   (BSP_IOMUXC_SW_PAD_CTL_PAD_ENET2_MAC0_MDIO_SEL, BSP_IOMUX_GPIO1_IO06_ALT0);
        
        BSP_IOMUX_SetMuxMode (BSP_IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07, BSP_IOMUX_ALT_1);

        DEF_BIT_SET(BSP_IOMUX_GPR1, DEF_BIT_18);                               /* Set the Tx clock direction for ENET2.                */

    } else {
       *p_err = NET_DEV_ERR_FAULT;                                             /* Invalid interface number.                            */
    }
                                                                               /* Configure GPIO6 & GPIO7's pad control registers.     */
    BSP_IOMUX_SetCtlReg (BSP_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06,
                         BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                         BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                         BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                         BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));
    
    BSP_IOMUX_SetCtlReg (BSP_IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07,
                         BSP_IOMUX_PAD_CTL_PAD_SRE  (BSP_IOMUX_SRE_FAST)      |
                         BSP_IOMUX_PAD_CTL_PAD_DSE  (BSP_IOMUX_DSE_48_OHM)    |
                         BSP_IOMUX_PAD_CTL_PAD_SPEED(BSP_IOMUX_SPEED_200MHZ)  |
                         BSP_IOMUX_PAD_CTL_PAD_PUE  (BSP_IOMUX_PUE_PULL)      |
                         BSP_IOMUX_PAD_CTL_PAD_PUS  (BSP_IOMUX_PUS_100K_OHM_PU));
    KAL_Dly(250u);
}


/*
*********************************************************************************************************
*                                         NetDev_ClkFreqGet()
*
* Description : Get device clock frequency.
*
* Argument(s) : p_if         Pointer to network interface to get clock frequency.
*               ----         Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device clock frequency     successfully
*                                                                   returned.
*                               NET_DEV_ERR_FAULT               Device clock frequency NOT successfully
*                                                                   returned.
*
* Return(s)   : Device clock frequency (in Hz).
*
* Caller(s)   : NetDev_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT32U  NetDev_ClkFreqGet (NET_IF   *p_if,
                                       NET_ERR  *p_err)
{
    CPU_INT32U  clk_freq;


   (void)&p_if;                                                 /* Prevent 'variable unused' compiler warning.          */

    clk_freq = NET_DEV_CLK_FREQ;
   *p_err    = NET_DEV_ERR_NONE;

    return (clk_freq);
}


/*
*********************************************************************************************************
*                                     NetDev_MACNetISR_Handler1()
*
* Description : BSP-level ISR handler(s) for device interrupts.
*
* Argument(s) : id      Not used.
*
* Return(s)   : none.
*
* Caller(s)   : CPU &/or device interrupts.
*
* Note(s)     : (1) (a) Each device interrupt, or set of device interrupts, MUST be handled by a
*                       unique BSP-level ISR handler which maps each specific device interrupt to
*                       its corresponding network interface ISR handler.
*
*                   (b) BSP-level device ISR handlers SHOULD be named using the following convention :
*
*                           NetDev_[Device]ISR_Handler[Type][Number]()
*
*                               where
*                                   (1) [Device]        Network device name or type (optional if the
*                                                           development board does NOT support multiple
*                                                           devices)
*                                   (2) [Type]          Network device interrupt type (optional if
*                                                           interrupt type is generic or unknown)
*                                   (3) [Number]        Network device number for each specific instance
*                                                           of device (optional if the development board
*                                                           does NOT support multiple instances of the
*                                                           specific device)
*
*                       See also 'NETWORK DEVICE BSP FUNCTION PROTOTYPES  Note #2a2'.
*********************************************************************************************************
*/

void  NetDev_MACNetISR_Handler1 (CPU_INT32U  id)
{
    NET_ERR  err;


   (void)id;

    NetIF_ISR_Handler(IMX6UL_MACNet_1_IF_Nbr, NET_DEV_ISR_TYPE_UNKNOWN, &err);
}


/*
*********************************************************************************************************
*                                     NetDev_MACNetISR_Handler2()
*
* Description : BSP-level ISR handler(s) for device interrupts.
*
* Argument(s) : id      Not used.
*
* Return(s)   : none.
*
* Caller(s)   : CPU &/or device interrupts.
*
* Note(s)     : (1) (a) Each device interrupt, or set of device interrupts, MUST be handled by a
*                       unique BSP-level ISR handler which maps each specific device interrupt to
*                       its corresponding network interface ISR handler.
*
*                   (b) BSP-level device ISR handlers SHOULD be named using the following convention :
*
*                           NetDev_[Device]ISR_Handler[Type][Number]()
*
*                               where
*                                   (1) [Device]        Network device name or type (optional if the
*                                                           development board does NOT support multiple
*                                                           devices)
*                                   (2) [Type]          Network device interrupt type (optional if
*                                                           interrupt type is generic or unknown)
*                                   (3) [Number]        Network device number for each specific instance
*                                                           of device (optional if the development board
*                                                           does NOT support multiple instances of the
*                                                           specific device)
*
*                       See also 'NETWORK DEVICE BSP FUNCTION PROTOTYPES  Note #2a2'.
*********************************************************************************************************
*/

void  NetDev_MACNetISR_Handler2 (CPU_INT32U  id)
{
    NET_ERR  err;


   (void)id;

    NetIF_ISR_Handler(IMX6UL_MACNet_2_IF_Nbr, NET_DEV_ISR_TYPE_UNKNOWN, &err);
}


#endif  /* NET_IF_ETHER_MODULE_EN */

