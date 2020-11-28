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
*                                   TCP/IP APPLICATION INITIALIZATION
*
*                                             NXP MCIMX6UL
*                                                on the
*
*                                       i.MX6 UltraLite EVK Board
*
* Filename : app_tcpip.c
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    APP_TCPIP_MODULE
#include  <os.h>
#include  "app_cfg.h"
#include  "app_tcpip.h"
#include  <bsp_net_macnet.h>
#include  "dhcp-c_cfg.h"
#include  <Source/dhcp-c.h>


/*
*********************************************************************************************************
*                                               ENABLE
*********************************************************************************************************
*/

#if (APP_CFG_TCPIP_EN == DEF_ENABLED)


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_TCPIP_ADDR_LEN                  15u
#define  APP_IF_MAX_CFGD                     DEF_MIN(NET_IF_CFG_MAX_NBR_IF, (APP_CFG_ENET1_EN + APP_CFG_ENET2_EN))


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

NET_IF_NBR  IMX6UL_NetInterfaces[NET_IF_CFG_MAX_NBR_IF];


/*
*********************************************************************************************************
*                                            LOCAL MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (NET_IPv6_CFG_EN == DEF_ENABLED)
static  void  AppTCPIP_AddrAutoCfgResult(       NET_IF_NBR                 if_nbr,
                                         const  NET_IPv6_ADDR             *p_addr_local_cfgd,
                                         const  NET_IPv6_ADDR             *p_addr_global_cfgd,
                                                NET_IPv6_AUTO_CFG_STATUS   auto_cfg_result);
#endif

#if (APP_CFG_ENET1_EN == DEF_ENABLED)
static  void  AppTCPIP_Init_ENET1       (       NET_ERR                   *p_err);
#endif
#if (APP_CFG_ENET2_EN == DEF_ENABLED)
static  void  AppTCPIP_Init_ENET2       (       NET_ERR                   *p_err);
#endif

CPU_BOOLEAN   AppDHCPc_InitMultipleIF   (       NET_IF_NBR                 if_nbr_tbl[],
                                                CPU_INT08U                 nbr_if_cfgd,
                                                DHCPc_STATUS               if_dhcp_result[]);

void          AppTCPIP_CfgStaticIPv4Addr(       CPU_CHAR                  *p_ip_addr,
                                                CPU_CHAR                  *p_subnet_msk,
                                                CPU_CHAR                  *p_gateway,
                                                NET_IF_NBR                *p_if_nbr,
                                                NET_ERR                   *p_err);

void          AppTCPIP_PrintIPAddr      (       NET_IF_NBR                 if_nbr);



/*
*********************************************************************************************************
*                                            AppTCPIP_Init()
*
* Description : Initializes uC/TCP-IP.
*
* Arguments   : none.
*
* Returns     : DEF_OK,   Initialization completed successfully.
*
*               DEF_FAIL, Initialization failed.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  AppTCPIP_Init (void)
{
    NET_ERR       net_err;
    NET_IF_NBR    interface_ix;
    NET_IF_NBR    if_max_cfgd;
#if (APP_CFG_DHCPc_EN == DEF_ENABLED)
    CPU_BOOLEAN   is_cfgd;
    DHCPc_STATUS  if_dhcp_result[2u];
#endif
    CPU_INT08U    hw_addr[6u];
    CPU_INT08U    hw_addr_len = 6u;


    APP_TRACE_INFO(("\r\n"));
    APP_TRACE_INFO(("===================================================================\r\n"));
    APP_TRACE_INFO(("=                       TCPIP INITIALIZATION                      =\r\n"));
    APP_TRACE_INFO(("===================================================================\r\n"));
    APP_TRACE_INFO(("Initializing TCPIP...\r\n"));
                                                                /* --------------------- INIT TCPIP ------------------- */
    APP_TRACE_INFO(("\r\n"));
    APP_TRACE_INFO(("------- i.MX6UL-EVK BOARD NETWORK CONFIG --------\r\n\r\n"));

                                                                /* Initialize TCPIP Core.                               */
    net_err = Net_Init(&NetRxTaskCfg,
                       &NetTxDeallocTaskCfg,
                       &NetTmrTaskCfg);
    if (net_err != NET_ERR_NONE) {
        APP_TRACE_INFO(("Net_Init() failed w/ err = %d \r\n", net_err));
        return (DEF_FAIL);
    }

    if_max_cfgd = APP_IF_MAX_CFGD;
    if (if_max_cfgd == 0u) {
        APP_TRACE_INFO(("uC/TCP-IP core intialized but no interfaces to configure.\r\n"));
        return (DEF_FAIL);
    } else { 
        for (interface_ix = 0u; (interface_ix < if_max_cfgd); interface_ix++) {
             IMX6UL_NetInterfaces[interface_ix] = NET_IF_NBR_NONE;
        }
    }
                                                                /* Initialize Interfaces.                               */
#if (APP_CFG_ENET1_EN == DEF_ENABLED)
    AppTCPIP_Init_ENET1(&net_err);
#endif
    KAL_Dly(200);                                                               
#if (APP_CFG_ENET2_EN == DEF_ENABLED)
    AppTCPIP_Init_ENET2(&net_err);
#endif


#if (APP_CFG_DHCPc_EN == DEF_ENABLED)                           /* Obtain IP address over DHCP.                         */
    is_cfgd = AppDHCPc_InitMultipleIF(IMX6UL_NetInterfaces,
                                      APP_IF_MAX_CFGD,
                                      if_dhcp_result);
    if (is_cfgd == DEF_TRUE) {
        APP_TRACE_INFO(("\r\n"));
        APP_TRACE_INFO(("DHCPc Success!\r\n"));
    }
#endif
    APP_TRACE_INFO(("\r\n"));
    APP_TRACE_INFO(("Network Configuration: \r\n"));
    interface_ix = NetIF_GetDflt();
                                                                /* Print the IP address of all configured interfaces.   */
    while (IMX6UL_NetInterfaces[interface_ix - 1u] != NET_IF_NBR_NONE &&
           interface_ix                            <= APP_IF_MAX_CFGD) {
        
        NetIF_AddrHW_Get( interface_ix,
                          hw_addr,
                         &hw_addr_len,
                         &net_err);

        APP_TRACE_INFO(("if%d: MAC %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",
                        interface_ix,
                        hw_addr[0u],
                        hw_addr[1u],
                        hw_addr[2u],
                        hw_addr[3u],
                        hw_addr[4u],
                        hw_addr[5u]));
        
        AppTCPIP_PrintIPAddr(interface_ix);
        interface_ix++;
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                               AppDHCPc_InitMultipleIF()
*
* Description : This function initialize uC/DHCPc and start DHCPc negotiation for many interfaces. This
*               function returns only the DHCP negotiation is completed.
*
* Argument(s) : if_nbr_tbl      Table that contains interface ID to be initialized with uC/DHCPc
*
*               nbr_if_cfgd     Number of interface to initialized (contained in tables)
*
*               if_dhcp_result  Table that will receive the DHCPc result of each interface to initialize.
*
* Return(s)   : DEF_OK,   Completed successfully.
*
*               DEF_FAIL, Initialization failed.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Prior to do any call to DHCPc the module must be initialized. If the process is successful,
*                   the DHCP client s tasks are started, and its various data structures are initialized.
*
*               (2) Start the DHCP management of the interfaces. Note that the interface is not configured yet upon
*                   returning from this function.
*
*               (3) An OS time delay must be applied between each call to DHCP to allow other task to run.
*
*               (4) Once the DHCP management of an interface has been started, the application may want to check the
*                   status of the lease negotiation in order to determine whether or not the interface has been properly
*                   configured:
*
*                   (a) Status DHCP_STATUS_CFG_IN_PROGRESS means that the negotiation is still underway.
*
*                   (b) Status DHCP_STATUS_CFGD indicates that the DHCP negotiation is done and that the interface is
*                       properly configured.
*
*                   (c) Status DHCP_STATUS_CFGD_NO_TMR specifies that the DHCP negotiation is done and that the interface
*                       is properly configured, but no timer has been set for renewing the lease. The effect of this is
*                       that the lease is going to be permanent, even though the server might have set a time limit for it.
*
*                   (d) Status DHCP_STATUS_CFGD_LOCAL_LINK means that the DHCP negotiation was not successful, and that a
*                       link-local address has been attributed to the interface. It is important to note that the DHCP
*                       client will not try to negotiate a lease with a server at this point.
*
*                   (e) Status DHCP_STATUS_FAIL denotes a negotiation error. At this point, the application should call
*                       the DHCPc_Stop() function and decide what to do next.
*********************************************************************************************************
*/

CPU_BOOLEAN  AppDHCPc_InitMultipleIF (NET_IF_NBR    if_nbr_tbl[],
                                      CPU_INT08U    nbr_if_cfgd,
                                      DHCPc_STATUS  if_dhcp_result[])
{
    NET_IF_NBR    if_nbr_cur;
    CPU_INT08U    nbr_if_init;
    CPU_INT08U    ix;
    DHCPc_STATUS  status;
    OS_ERR        os_err;
    DHCPc_ERR     err;


                                                                /* --------------- INITIALIZE uC/DHCPc ---------------- */
    err = DHCPc_Init();                                         /* See Note #1.                                         */
    if (err != DHCPc_ERR_NONE) {
        return (DEF_FAIL);
    }

    OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_DLY, &os_err);      /* See Note #3.                                         */
                                                                /* ----------- START DHCPC ON EACH INTERFACE ---------- */
    for (ix = 0; ix < nbr_if_cfgd; ix++) {
        if_nbr_cur         = if_nbr_tbl[ix];
        if_dhcp_result[ix] = DHCP_STATUS_NONE;
        DHCPc_Start( if_nbr_cur,                                /* See Note #2.                                         */
                     DEF_NULL,
                     0,
                    &err);
        if (err != DHCPc_ERR_NONE) {
            if (if_nbr_cur < nbr_if_cfgd) { 
                continue;
            } else {
                break;
            }
        }
        if_dhcp_result[ix] = DHCP_STATUS_CFG_IN_PROGRESS;
        OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_DLY, &os_err);  /* See Note #3.                                         */
    }

    nbr_if_init = 0u;
                                                                /* ------ WAIT UNTIL NEGOTIATIONS ARE COMPLETED ------- */
    while (nbr_if_init < nbr_if_cfgd) {
        OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_DLY, &os_err);  /* See Note #3.                                         */

        for (ix = 0; ix < nbr_if_cfgd; ix++) {
            if (if_dhcp_result[ix] == DHCP_STATUS_CFG_IN_PROGRESS) {
                if_nbr_cur = if_nbr_tbl[ix];
                status     = DHCPc_ChkStatus(if_nbr_cur, &err); /* Check DHCP status. See Note #4.                      */
                switch (status) {
                    case DHCP_STATUS_CFG_IN_PROGRESS:           /* See Note #4a.                                        */
                         break;


                    case DHCP_STATUS_CFGD:                      /* See Note #4b.                                        */
                    case DHCP_STATUS_CFGD_NO_TMR:               /* See Note #4c.                                        */
                    case DHCP_STATUS_CFGD_LOCAL_LINK:           /* See Note #4d.                                        */
                    case DHCP_STATUS_FAIL:                      /* See Note #4e.                                        */
                         if_dhcp_result[ix] = status;           /* Store negotiation result.                            */
                         nbr_if_init++;
                         break;


                    default:
                         break;
                }
            }
        }
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                          AppTCPIP_Init_ENET1()
*
* Description : Initializes ENET1 interface.
*
* Arguments   : p_err   Pointer to variable to store NET_ERR return code.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (APP_CFG_ENET1_EN == DEF_ENABLED)
static  void  AppTCPIP_Init_ENET1 (NET_ERR  *p_err)
{
    NET_IF_NBR   if_nbr_enet1;
#if (NET_IPv6_CFG_EN == DEF_ENABLED)
    CPU_BOOLEAN  detect_dup_addr;
#endif
    NET_IF_NBR   interface_ix;
    NET_ERR      net_err;
    

    APP_TRACE_INFO(("\r\n\r\n"));
    APP_TRACE_INFO(("Starting ENET1...\r\n\r\n"));
    
                                                                /* -------------- ETHERNET CONFIGURATION -------------- */
    if_nbr_enet1 = NetIF_Add((void              *)&NetIF_API_Ether,              /* Ethernet API                        */
                             (void              *)&NetDev_API_MACNET,            /* Device API structure                */
                             (void              *)&NetDev_BSP_MACNet_1,          /* Device BSP structure                */
                             (NET_DEV_CFG_ETHER *)&NetDev_Cfg_MACNet_ETHER1,     /* Device Configuration structure      */
                             /*(void              *)&NetPhy_API_KSZ8081RNB,*/        /* PHY API structure                   */
                             (void              *)&NetPhy_API_Generic,          /* PHY API structure                   */
                             (void              *)&NetPhy_Cfg_MACNet_ETHER1,     /* PHY Configuration structure         */
                                                  &net_err);                     /* Return error variable               */

    if (net_err != NET_IF_ERR_NONE) {
        APP_TRACE_INFO(("NetIF_Add() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }

    for (interface_ix = 0u; interface_ix < APP_IF_MAX_CFGD; interface_ix++) {
         if (IMX6UL_NetInterfaces[interface_ix] == NET_IF_NBR_NONE) {
             IMX6UL_NetInterfaces[interface_ix] = if_nbr_enet1;
             break;
         }
    }

                                                                /* ------------------ START IF NBR 1 ------------------ */
    NetIF_Start(if_nbr_enet1, &net_err);
    if (net_err != NET_IF_ERR_NONE) {
        APP_TRACE_INFO(("NetIF_Start() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }

    NetIF_LinkStateWaitUntilUp(if_nbr_enet1, 20, 200, &net_err);
    if (net_err != NET_IF_ERR_NONE) {
        APP_TRACE_INFO(("NetIF_LinkStateWaitUntilUp() failed w/ err = %d \r\n", net_err));
        NetIF_Stop(if_nbr_enet1, &net_err);
       *p_err = net_err;
        return;
    }

                                                                /* ---------------- CFG IF NBR 1 (IPv4) --------------- */
    AppTCPIP_CfgStaticIPv4Addr( APP_CFG_TCPIP_ENET1_IP_ADDR_IPv4,
                                APP_CFG_TCPIP_ENET1_SUBNET_MASK_IPv4, 
                                APP_CFG_TCPIP_ENET1_DFLT_GATEWAY_IPv4,
                               &if_nbr_enet1,
                               &net_err);
    if (net_err != NET_IPv4_ERR_NONE) {
        APP_TRACE_INFO(("AppTCPIP_CfgStaticIPv4Addr() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }

#if (NET_IPv6_CFG_EN == DEF_ENABLED)
                                                                /* ---------------- CFG IF NBR 1 (IPv6) --------------- */
    NetIPv6_AddrAutoCfgHookSet(if_nbr_enet1, AppTCPIP_AddrAutoCfgResult, &net_err);
    if (net_err != NET_IPv6_ERR_NONE) {
        APP_TRACE_INFO(("NetIPv6_AddrAutoCfgHookSet() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }

    APP_TRACE_INFO(("Starting IPv6 Auto-Configuration.\r\n\r\n"));
    detect_dup_addr = DEF_TRUE;
    NetIPv6_AddrAutoCfgEn(if_nbr_enet1, detect_dup_addr, &net_err);
    if (net_err != NET_IPv6_ERR_NONE) {
        APP_TRACE_INFO(("NetIPv6_AddrAutoCfgEn() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }
#endif
    APP_TRACE_INFO(("ENET1 successfully added\r\n\r\n"));
}
#endif


/*
*********************************************************************************************************
*                                          AppTCPIP_Init_ENET2()
*
* Description : Initializes ENET2 interface.
*
* Arguments   : p_err   Pointer to variable to store NET_ERR return code.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (APP_CFG_ENET2_EN == DEF_ENABLED)
static  void  AppTCPIP_Init_ENET2 (NET_ERR  *p_err)
{
    NET_IF_NBR   if_nbr_enet2;
#if (NET_IPv6_CFG_EN == DEF_ENABLED)
    CPU_BOOLEAN  detect_dup_addr;
#endif
    NET_IF_NBR   interface_ix;
    NET_ERR      net_err;


    APP_TRACE_INFO(("\r\n\r\n"));
    APP_TRACE_INFO(("Starting ENET2...\r\n\r\n"));    
                                                                /* -------------- ETHERNET CONFIGURATION -------------- */
    if_nbr_enet2 = NetIF_Add((void              *)&NetIF_API_Ether,              /* Ethernet API                        */
                             (void              *)&NetDev_API_MACNET,            /* Device API structure                */
                             (void              *)&NetDev_BSP_MACNet_2,          /* Device BSP structure                */
                             (NET_DEV_CFG_ETHER *)&NetDev_Cfg_MACNet_ETHER2,     /* Device Configuration structure      */
                             /*(void              *)&NetPhy_API_KSZ8081RNB,*/        /* PHY API structure                   */
                             (void              *)&NetPhy_API_Generic,          /* PHY API structure                   */
                             (void              *)&NetPhy_Cfg_MACNet_ETHER2,     /* PHY Configuration structure         */
                                                  &net_err);                     /* Return error variable               */

    if (net_err != NET_IF_ERR_NONE) {
        APP_TRACE_INFO(("NetIF_Add() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }

    for (interface_ix = 0u; interface_ix < APP_IF_MAX_CFGD; interface_ix++) {
         if (IMX6UL_NetInterfaces[interface_ix] == NET_IF_NBR_NONE) {
             IMX6UL_NetInterfaces[interface_ix] = if_nbr_enet2;
             break;
         }
    }
                                                                /* ------------------ START IF NBR 2 ------------------ */
    NetIF_Start(if_nbr_enet2, &net_err);
    if (net_err != NET_IF_ERR_NONE) {
        APP_TRACE_INFO(("NetIF_Start() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }

    NetIF_LinkStateWaitUntilUp(if_nbr_enet2, 20, 200, &net_err);
    if (net_err != NET_IF_ERR_NONE) {
        APP_TRACE_INFO(("NetIF_LinkStateWaitUntilUp() failed w/ err = %d \r\n", net_err));
        NetIF_Stop(if_nbr_enet2, &net_err);
       *p_err = net_err;
        return;
    }
                                                                /* ---------------- CFG IF NBR 2 (IPv4) --------------- */

    AppTCPIP_CfgStaticIPv4Addr( APP_CFG_TCPIP_ENET2_IP_ADDR_IPv4,
                                APP_CFG_TCPIP_ENET2_SUBNET_MASK_IPv4, 
                                APP_CFG_TCPIP_ENET2_DFLT_GATEWAY_IPv4,
                               &if_nbr_enet2,
                               &net_err);

    if (net_err != NET_IPv4_ERR_NONE) {
        APP_TRACE_INFO(("AppTCPIP_CfgStaticIPv4Addr() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }

#if (NET_IPv6_CFG_EN == DEF_ENABLED)
                                                                /* ---------------- CFG IF NBR 2 (IPv6) --------------- */
    NetIPv6_AddrAutoCfgHookSet(if_nbr_enet2, AppTCPIP_AddrAutoCfgResult, &net_err);
    if (net_err != NET_IPv6_ERR_NONE) {
        APP_TRACE_INFO(("NetIPv6_AddrAutoCfgHookSet() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }
    
    APP_TRACE_INFO(("Starting IPv6 Auto-Configuration.\r\n\r\n"));
    detect_dup_addr = DEF_TRUE;
    NetIPv6_AddrAutoCfgEn(if_nbr_enet2, detect_dup_addr, &net_err);
    if (net_err != NET_IPv6_ERR_NONE) {
        APP_TRACE_INFO(("NetIPv6_AddrAutoCfgEn() failed w/ err = %d \r\n", net_err));
       *p_err = net_err;
        return;
    }
#endif
    APP_TRACE_INFO(("ENET2 successfully added\r\n\r\n"));
}
#endif

/*
*********************************************************************************************************
*                                         AppTCPIP_PrintIPAddr()
*
* Description : Obtain IP Address, Subnet Mask, & Default Gateway of connection based on Interface Number
*
* Arguments   : if_nbr  Interface Number to obtain TCP/IP connection information.
*
* Return(s)   : none.
*
* Caller(s)   : AppTCPIP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#ifdef  NET_IPv4_MODULE_EN
void  AppTCPIP_PrintIPAddr (NET_IF_NBR  if_nbr)
{
    NET_IPv4_ADDR     ip_addr_tbl[NET_IPv4_CFG_IF_MAX_NBR_ADDR];
    NET_IPv4_ADDR     subnet_addr;
    NET_IPv4_ADDR     gateway_addr;
    NET_IP_ADDRS_QTY  ip_addr_tbl_qty;
    NET_ERR           net_err;
    CPU_CHAR          app_ip_addr[APP_TCPIP_ADDR_LEN];
    CPU_CHAR          app_subnet_addr[APP_TCPIP_ADDR_LEN];
    CPU_CHAR          app_gateway_addr[APP_TCPIP_ADDR_LEN];


    Mem_Clr(&app_ip_addr,      sizeof(app_ip_addr  ));          /* Init Var(s).                                         */
    Mem_Clr(&app_subnet_addr,  sizeof(app_ip_addr  ));
    Mem_Clr(&app_gateway_addr, sizeof(app_ip_addr  ));

    ip_addr_tbl_qty = sizeof(ip_addr_tbl) / sizeof(NET_IPv4_ADDR);

    NetIPv4_GetAddrHost( if_nbr,                                /* Get IPv4 Host Addresses based on Interface Number.   */
                        &ip_addr_tbl[0u],
                        &ip_addr_tbl_qty,
                        &net_err);

    if (net_err != NET_IPv4_ERR_NONE) {
        APP_TRACE_INFO(("NetIPv4_GetAddrHost() failed w/err = %d \r\n", net_err));
        return;
    }
                                                                /* Get IPv4 Subnet Mask & Dflt Gateway from Host Addr   */
    subnet_addr  = NetIPv4_GetAddrSubnetMask (ip_addr_tbl[0u], &net_err);
    gateway_addr = NetIPv4_GetAddrDfltGateway(ip_addr_tbl[0u], &net_err);

    NetASCII_IPv4_to_Str( ip_addr_tbl[0u],                      /* Set IPv4 IP Address to string.                       */
                         &app_ip_addr[0u],
                          DEF_NO,
                         &net_err);

    NetASCII_IPv4_to_Str( subnet_addr,                          /* Set IPv4 Subnet Mask to String.                      */
                         &app_subnet_addr[0u],
                          DEF_NO,
                         &net_err);

    NetASCII_IPv4_to_Str( gateway_addr,                         /* Set IPv4 Default Gateway to String.                  */
                         &app_gateway_addr[0u],
                          DEF_NO,
                         &net_err);
                                                                /* -------------------- DISPLAY ADDR ------------------ */
    APP_TRACE_INFO(("IPv4 Address    : %s \r\n", app_ip_addr     ));
    APP_TRACE_INFO(("Subnet Mask     : %s \r\n", app_subnet_addr ));
    APP_TRACE_INFO(("Default Gateway : %s \r\n", app_gateway_addr));
    APP_TRACE_INFO(("\r\n"));
}
#endif


/*
*********************************************************************************************************
*                                          AppTCPIP_CfgStaticIPv4Addr()
*
* Description : Configure a static IPv4 address on the indicated interface.
*
* Argument(s) : p_ip_addr       String denoting static IPv4 address to configure.
*
*               p_subnet_msk:   String indicating the subnet mask.
*
*               p_gateway:      String indicating the default gateway.
*
*               if_nbr:         Number of initialized interface for which this IP address will be assigned.
*
*               p_err:          Pointer to variable to store NET_ERR return code.
*
* Return(s)   : None.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  AppTCPIP_CfgStaticIPv4Addr (CPU_CHAR    *p_ip_addr,
                                  CPU_CHAR    *p_subnet_msk,
                                  CPU_CHAR    *p_gateway,
                                  NET_IF_NBR  *p_if_nbr,
                                  NET_ERR     *p_err)
{
    NET_IPv4_ADDR  ip;
    NET_IPv4_ADDR  msk;
    NET_IPv4_ADDR  gateway;
    NET_ERR        net_err;


    ip      = NetASCII_Str_to_IPv4((CPU_CHAR *)p_ip_addr,    &net_err);
    msk     = NetASCII_Str_to_IPv4((CPU_CHAR *)p_subnet_msk, &net_err);
    gateway = NetASCII_Str_to_IPv4((CPU_CHAR *)p_gateway,    &net_err);
    
    NetIPv4_CfgAddrAdd(*p_if_nbr,
                        ip,
                        msk,
                        gateway,
                       &net_err);

   *p_err = net_err;
}


/*
*********************************************************************************************************
*                                          App_AutoCfgResult()
*
* Description : Hook function to received the IPv6 Auto-Configuration process result.
*
* Argument(s) : if_nbr               Network Interface number on which Auto-Configuration occurred.
*
*               p_addr_local_cfgd    Pointer to IPv6 link-local address configured, if any.
*                                    DEF_NULL, otherwise.
*
*               p_addr_global_cfgd   Pointer to IPv6 global address configured, if any.
*                                    DEF_NULL, otherwise.
*
*               auto_cfg_result      Result status of the IPv6 Auto-Configuration process.
*
* Return(s)   : None.
*
* Caller(s)   : AppTCPIP_Init().
*
* Note(s)     : None.
*********************************************************************************************************
*/

#if (NET_IPv6_CFG_EN == DEF_ENABLED)
static  void  AppTCPIP_AddrAutoCfgResult (       NET_IF_NBR                 if_nbr,
                                          const  NET_IPv6_ADDR             *p_addr_local_cfgd,
                                          const  NET_IPv6_ADDR             *p_addr_global_cfgd,
                                                 NET_IPv6_AUTO_CFG_STATUS   auto_cfg_result)
{
    CPU_CHAR  ip_str[NET_ASCII_LEN_MAX_ADDR_IPv6];
    NET_ERR   net_err;


    switch (auto_cfg_result) {
        case NET_IPv6_AUTO_CFG_STATUS_FAILED:
             APP_TRACE_INFO(("IPv6 Auto-Configuration failed.\r\n\r\n"));
             break;


        case NET_IPv6_AUTO_CFG_STATUS_SUCCEEDED:
             APP_TRACE_INFO(("IPv6 Auto-Configuration succeeded.\r\n\r\n"));
             break;


        case NET_IPv6_AUTO_CFG_STATUS_LINK_LOCAL:
             APP_TRACE_INFO(("IPv6 Auto-Configuration succeeded. (Link-Local only.)\r\n\r\n"));
             break;


        default:
             APP_TRACE_INFO(("Unknown IPv6 Auto-Configuration result.\r\n\r\n"));
             break;
    }

    if (p_addr_local_cfgd != DEF_NULL) {
        NetASCII_IPv6_to_Str((NET_IPv6_ADDR *)p_addr_local_cfgd, ip_str, DEF_NO, DEF_YES, &net_err);
        APP_TRACE_INFO(("\tLink-Local Address on \"if%d\": %s\r\n", if_nbr, ip_str));
    }

    if (p_addr_global_cfgd != DEF_NULL) {
        NetASCII_IPv6_to_Str((NET_IPv6_ADDR *)p_addr_global_cfgd, ip_str, DEF_NO, DEF_YES, &net_err);
        APP_TRACE_INFO(("\tGlobal Address    : %s\r\n", ip_str));
    }
}
#endif


/*
*********************************************************************************************************
*                                             ENABLE END
*********************************************************************************************************
*/

#endif
