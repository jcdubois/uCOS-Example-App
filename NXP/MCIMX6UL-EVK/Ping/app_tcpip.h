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
*                                             EXAMPLE CODE
*
*                                             NXP MCIMX6UL
*                                                on the
*
*                                       i.MX6 UltraLite EVK Board
*
* Filename : app_tcpip.h
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This file system application header file is protected from multiple pre-processor
*               inclusion through use of the TCP/IP application present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  APP_TCPIP_MODULE_PRESENT
#define  APP_TCPIP_MODULE_PRESENT


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   APP_TCPIP_MODULE
#define  APP_TCPIP_EXT
#else
#define  APP_TCPIP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <app_cfg.h>


/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/

#ifndef  APP_CFG_TCPIP_EN
#define  APP_CFG_TCPIP_EN                       DEF_DISABLED
#endif


/*
*********************************************************************************************************
*                                      CONDITIONAL INCLUDE FILES
*********************************************************************************************************
*/

#if (APP_CFG_TCPIP_EN == DEF_ENABLED)
#include  <net_cfg.h>
#include  <net_dev_cfg.h>
#include  <bsp_net_macnet.h>
#include  <IF/net_if.h>
#include  <IF/net_if_ether.h>
#include  <Source/net.h>
#include  <IP/IPv4/net_ipv4.h>
#include  <IP/IPv6/net_ipv6.h>
#include  <Dev/Ether/MACNet/net_dev_macnet.h>
/* #include  <Dev/Ether/PHY/KSZ8081RNB/net_phy_ksz8081rnb.h> */
/* #include  <Dev/Ether/PHY/KSZ9021r/net_phy_ksz9021r.h> */
#include  <Dev/Ether/PHY/Generic/net_phy.h>
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (APP_CFG_TCPIP_EN == DEF_ENABLED)
CPU_BOOLEAN  AppTCPIP_Init(void);
#endif


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  APP_CFG_TCPIP_EN
#error  "APP_CFG_TCPIP_EN                                             not #define'd in 'app_cfg.h'"
#error  "                                                       [MUST be  DEF_DISABLED]           "
#error  "                                                       [     ||  DEF_ENABLED ]           "

#elif  ((APP_CFG_TCPIP_EN != DEF_DISABLED) && \
        (APP_CFG_TCPIP_EN != DEF_ENABLED ))
#error  "APP_CFG_TCPIP_EN                                       illegally #define'd in 'app_cfg.h'"
#error  "                                                       [MUST be  DEF_DISABLED]           "
#error  "                                                       [     ||  DEF_ENABLED ]           "

#endif


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : See 'MODULE  Note #1'.
*********************************************************************************************************
*/

#endif                                                          /* End of TCP/IP app module include (see Note #1).      */
