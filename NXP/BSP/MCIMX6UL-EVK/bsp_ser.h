/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2016; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               This BSP is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                         i.MX UART INTERFACE
*
*********************************************************************************************************
*/


#ifndef  BSP_SER_H
#define  BSP_SER_H

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>

/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  BSP_SER_PRINTF_STR_BUF_SIZE             128u          /* Maximum string length.                               */


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void        BSP_Ser_Init        (void);

CPU_CHAR    BSP_Ser_RdByte      (void);

void        BSP_Ser_RdStr       (CPU_CHAR    *p_str,
                                 CPU_INT16U   len);

void        BSP_Ser_WrByte      (CPU_INT08U   c);

void        BSP_Ser_WrStr       (CPU_CHAR    *p_str);

void        BSP_Ser_Printf      (CPU_CHAR    *format,
                                 ...);

#endif /* BSP_SER_H */
