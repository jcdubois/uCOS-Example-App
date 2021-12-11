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
*                                              i.MX UART
*
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <stdint.h>
#include  <string.h>
#include  <stdarg.h>
#include  <stdio.h>

//#include  "../include/bsp.h"
#include  "bsp_ser.h"
//#include  "../include/imx_defs.h"

#include  <lib_def.h>
#include  <os.h>
#include  <KAL/kal.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

extern volatile char _uart_start;

#define  IMX_UART1_BASE ((CPU_ADDR)(&_uart_start))

#define  IMX6_UART_UART1_UCRX (*((CPU_REG32 *)(IMX_UART1_BASE + 0x00)))
#define  IMX6_UART_UART1_UCTX (*((CPU_REG32 *)(IMX_UART1_BASE + 0x40)))

#define  IMX6_UART_UART1_UCR1 (*((CPU_REG32 *)(IMX_UART1_BASE + 0x80)))
#define  IMX6_UART_UART1_UCR2 (*((CPU_REG32 *)(IMX_UART1_BASE + 0x84)))
#define  IMX6_UART_UART1_UCR3 (*((CPU_REG32 *)(IMX_UART1_BASE + 0x88)))

#define  IMX6_UART_UART1_UBIR (*((CPU_REG32 *)(IMX_UART1_BASE + 0xA4)))
#define  IMX6_UART_UART1_UBMR (*((CPU_REG32 *)(IMX_UART1_BASE + 0xA8)))

#define  IMX6_UART_UART1_UFCR (*((CPU_REG32 *)(IMX_UART1_BASE + 0x90)))

#define  IMX6_UART_UART1_ONEMS (*((CPU_REG32 *)(IMX_UART1_BASE + 0xB0)))

#define  IMX6_UART_UART1_UTS (*((CPU_REG32 *)(IMX_UART1_BASE + 0xB4)))


/*
*********************************************************************************************************
*                                         LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

//static  KAL_SEM_HANDLE   BSP_SerTxWait;
//static  KAL_SEM_HANDLE   BSP_SerRxWait;
static  KAL_SEM_HANDLE   BSP_SerLock;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

#define CCGR148 (*((CPU_REG32 *)0x30384940u))

void  BSP_Ser_Init (void)
{
    RTOS_ERR  rtos_err;

#if (IMX_CPU_TYPE == CPU_IMX7)
    CCGR148 = 0x3333;
#endif
                                                                /* ----------------- INIT OS OBJECTS ------------------ */
    //BSP_SerTxWait = KAL_SemCreate("Serial Tx Wait", DEF_NULL, &rtos_err);
    //BSP_SerRxWait = KAL_SemCreate("Serial Rx Wait", DEF_NULL, &rtos_err);
    BSP_SerLock = KAL_SemCreate("Serial Lock", DEF_NULL, &rtos_err);
    KAL_SemSet(BSP_SerLock, 1u, &rtos_err);

#if 0
    /* IOMUXC configuration for the IMX6Q-SDB */
    DEF_BIT_FIELD_WR(IMX6_IOMUXC_MUX_CTL_GPIO1_IO04, 0x0, DEF_BIT_FIELD(3u, 0u));
    DEF_BIT_FIELD_WR(IMX6_IOMUXC_MUX_CTL_UART1_URDSI, 0x0, DEF_BIT_FIELD(2u, 0u));

    DEF_BIT_FIELD_WR(IMX6_IOMUXC_MUX_CTL_GPIO1_IO05, 0x0, DEF_BIT_FIELD(3u, 0u));
    DEF_BIT_FIELD_WR(IMX6_IOMUXC_MUX_CTL_UART1_URDSI, 0x0, DEF_BIT_FIELD(2u, 0u));

    IMX6_IOMUXC_MUX_PAD_GPIO1_IO04 = 0x1B0B0;
    IMX6_IOMUXC_MUX_PAD_GPIO1_IO05 = 0x1B0B0;
#endif

    DEF_BIT_FIELD_WR(IMX6_UART_UART1_UFCR, 0x5, DEF_BIT_FIELD(3u, 7u)); /* Divide by 1.                                 */

    IMX6_UART_UART1_UCR2 = 0;
    DEF_BIT_SET(IMX6_UART_UART1_UCR2, DEF_BIT_05);              /* 8 bit word size.                                     */
    IMX6_UART_UART1_UCR3 = DEF_BIT_02;

    IMX6_UART_UART1_UCR1 = DEF_BIT_00;

    DEF_BIT_SET(IMX6_UART_UART1_UCR2, DEF_BIT_14);              /* Ignore CTS.                                          */
    DEF_BIT_SET(IMX6_UART_UART1_UCR2, DEF_BIT_01);              /* Enable RX.                                           */
    DEF_BIT_SET(IMX6_UART_UART1_UCR2, DEF_BIT_02);              /* Enable TX.                                           */
    DEF_BIT_SET(IMX6_UART_UART1_UCR2, DEF_BIT_00);              /* De-assert reset.                                     */

    /* Default configuration for 115200 at 80Mhz ref clock. */
#if (IMX_CPU_TYPE == CPU_IMX7)
    IMX6_UART_UART1_UBIR = 99u;
    IMX6_UART_UART1_UBMR = 1307u;
#endif

#if (IMX_CPU_TYPE == CPU_IMX6)
    IMX6_UART_UART1_UBIR = 1151u;
    IMX6_UART_UART1_UBMR = 49999u;
#endif

    /* Disable debug halt. */
    IMX6_UART_UART1_UTS |= DEF_BIT_11 | DEF_BIT_09;

}


/*
*********************************************************************************************************
*                                          BSP_Ser_WrByteUnlocked()
*
* Description : Writes a single byte to a serial port.
*
* Argument(s) : c           The character to output.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Ser_WrByte()
*               BSP_Ser_WrByteUnlocked()
*
* Note(s)     : (1) This function blocks until room is available in the UART for the byte to be sent.
*********************************************************************************************************
*/

static void  BSP_Ser_WrByteUnlocked(CPU_INT08U  c)
{
    while (DEF_BIT_IS_SET(IMX6_UART_UART1_UTS, DEF_BIT_04)) {
        ;
    }

    IMX6_UART_UART1_UCTX = c;
}


/*
*********************************************************************************************************
*                                                BSP_Ser_WrByte()
*
* Description : Writes a single byte to a serial port.
*
* Argument(s) : tx_byte     The character to output.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Ser_WrByte(CPU_INT08U  c)
{
    RTOS_ERR  rtos_err;


    KAL_SemPend(BSP_SerLock, 0u, 0u, &rtos_err);

    BSP_Ser_WrByteUnlocked(c);

    KAL_SemPost(BSP_SerLock, 0u, &rtos_err);
}


/*
*********************************************************************************************************
*                                                BSP_Ser_WrStr()
*
* Description : Transmits a string.
*
* Argument(s) : p_str       Pointer to the string that will be transmitted.
*
* Caller(s)   : Application.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Ser_WrStr (CPU_CHAR  *p_str)
{
    RTOS_ERR  rtos_err;


    if (p_str == DEF_NULL) {
        return;
    }

    KAL_SemPend(BSP_SerLock, 0u, 0u, &rtos_err);

    while ((*p_str) != DEF_NULL) {
        BSP_Ser_WrByteUnlocked(*p_str++);
    }

    KAL_SemPost(BSP_SerLock, 0u, &rtos_err);
}


/*
*********************************************************************************************************
*                                                BSP_Ser_RdByte()
*
* Description : Receive a single byte.
*
* Argument(s) : none.
*
* Return(s)   : The received byte.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This functions blocks until a data is received.
*
*               (2) It can not be called from an ISR.
*********************************************************************************************************
*/

CPU_CHAR  BSP_Ser_RdByte (void)
{
    RTOS_ERR  rtos_err;
    CPU_INT32U c;

    KAL_SemPend(BSP_SerLock, 0u, 0u, &rtos_err);

    while (DEF_BIT_IS_SET(IMX6_UART_UART1_UTS, DEF_BIT_05)) {
        ;
    }

    c = IMX6_UART_UART1_UCRX;

    KAL_SemPost(BSP_SerLock, 0u, &rtos_err);

    return ((CPU_INT08U)c);
}

#if 0
/*
*********************************************************************************************************
*                                           BSP_Ser_Printf()
*
* Description : Print formatted data to the output serial port.
*
* Argument(s) : format      String that contains the text to be written.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function output a maximum of BSP_SER_PRINTF_STR_BUF_SIZE number of bytes to the
*                   serial port.  The calling function hence has to make sure the formatted string will
*                   be able fit into this string buffer or hence the output string will be truncated.
*********************************************************************************************************
*/

void  BSP_Ser_Printf (CPU_CHAR  *format, ...)
{
    CPU_CHAR  buf_str[BSP_SER_PRINTF_STR_BUF_SIZE + 1u];
    va_list   v_args;


    va_start(v_args, format);
   (void)vsnprintf((char       *)&buf_str[0],
                   (size_t      ) sizeof(buf_str),
                   (char const *) format,
                                  v_args);
    va_end(v_args);

    BSP_Ser_WrStr(buf_str);
}
#endif
