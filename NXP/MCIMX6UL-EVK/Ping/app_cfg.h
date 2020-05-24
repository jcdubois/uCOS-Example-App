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
* Filename : app_cfg.h
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                INCLUDE
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

#include  <cpu.h>
#include  <stdio.h>


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  APP_CFG_TCPIP_EN                            DEF_ENABLED


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_STARTUP_TASK_PRIO                        2u
#define  NET_CFG_TASK_TX_DEALLOC_PRIO                     4u
#define  DHCPc_OS_CFG_TASK_PRIO                           5u
#define  DHCPc_OS_CFG_TMR_TASK_PRIO                       6u
#define  NET_CFG_TASK_TMR_PRIO                            7u
#define  NET_CFG_TASK_RX_PRIO                             8u


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_CFG_TASK_STARTUP_STK_SIZE                 4096u
#define  DHCPc_OS_CFG_TASK_STK_SIZE                    1024u
#define  DHCPc_OS_CFG_TMR_TASK_STK_SIZE                1024u
#define  NET_CFG_TASK_RX_STK_SIZE                      8192u
#define  NET_CFG_TASK_TX_DEALLOC_STK_SIZE              8192u
#define  NET_CFG_TASK_TMR_STK_SIZE                     8192u


/*
*********************************************************************************************************
*                                          NETWORK CONFIGURATIONS
*********************************************************************************************************
*/

#define  APP_CFG_TCPIP_ENET1_IP_ADDR_IPv4                 "192.168.2.25"
#define  APP_CFG_TCPIP_ENET1_SUBNET_MASK_IPv4             "255.255.255.0"
#define  APP_CFG_TCPIP_ENET1_DFLT_GATEWAY_IPv4            "192.168.2.1"

#define  APP_CFG_TCPIP_ENET2_IP_ADDR_IPv4                 "192.168.2.26"
#define  APP_CFG_TCPIP_ENET2_SUBNET_MASK_IPv4             "255.255.255.0"
#define  APP_CFG_TCPIP_ENET2_DFLT_GATEWAY_IPv4            "192.168.2.1"

#define  APP_CFG_ENET1_EN                                 DEF_ENABLED
#define  APP_CFG_ENET2_EN                                 DEF_ENABLED
#define  APP_CFG_DHCPc_EN                                 DEF_DISABLED


/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#ifndef  TRACE_LEVEL_OFF
#define  TRACE_LEVEL_OFF                                   0
#endif

#ifndef  TRACE_LEVEL_INFO
#define  TRACE_LEVEL_INFO                                  1
#endif

#ifndef  TRACE_LEVEL_DBG
#define  TRACE_LEVEL_DBG                                   2
#endif

#define  APP_CFG_TRACE_LEVEL                       TRACE_LEVEL_OFF
#define  APP_CFG_TRACE                             printf

#define  APP_TRACE_INFO(x)               ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_CFG_TRACE x) : (void)0)


#endif /* __APP_CFG_H__ */
