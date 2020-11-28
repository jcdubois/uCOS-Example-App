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
* Filename : main.c
*********************************************************************************************************
* Note(s) : none.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <os.h>
#include  <cpu.h>
#include  <cpu_core.h>
#include  <lib_mem.h>
#include  <lib_str.h>

#include  "../app_cfg.h"
#include  "os_app_hooks.h"

#if (APP_CFG_TCPIP_EN > 0u)
#include  <Source/net.h>
#include  "../app_tcpip.h"
#endif

#include  <bsp_os.h>
#include  <bsp_iomux.h>
#include  <bsp_gpio.h>
#include  <bsp_sys.h>
#include  <bsp_int.h>
#include  <bsp_ser.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

                                                                /* ----------------- APPLICATION GLOBALS ------------------ */
static  CPU_STK  StartupTaskStk[APP_CFG_TASK_STARTUP_STK_SIZE];
static  OS_TCB   StartupTaskTCB;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  StartupTask(void  *p_arg);

long long __aeabi_ldiv0(long long r)
{
	while(1);
}

void _putchar(char character)
{
	BSP_Ser_WrByte(character);
}

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int main(void)
{
    OS_ERR  os_err;


    BSP_SysInit();                                              /* Initialize the main clock                            */
    BSP_IntInit();                                              /* Initialize RAM interrupt vector table                */
    BSP_OS_TickInit(OSCfg_TickRate_Hz);                         /* Initialize kernel tick timer                         */
    
    
    Mem_Init();                                                 /* Initialize Memory Managment Module                   */
    CPU_IntDis();                                               /* Disable all Interrupts                               */
    CPU_Init();                                                 /* Initialize the uC/CPU services                       */

    OSInit(&os_err);                                            /* Init uC/OS-III.                                      */
    if (os_err != OS_ERR_NONE) {
        while (1);
    }

    App_OS_SetAllHooks();

    OSTaskCreate(&StartupTaskTCB,                               /* Create the start task                                */
                 "Startup Task",
                  StartupTask,
                  0,
                  APP_CFG_STARTUP_TASK_PRIO,
                 &StartupTaskStk[0u],
                  APP_CFG_TASK_STARTUP_STK_SIZE / 10u,
                  APP_CFG_TASK_STARTUP_STK_SIZE,
                  0u,
                  0u,
                  0,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);
    if (os_err != OS_ERR_NONE) {
        while (1);
    }

    OSStart(&os_err);                                           /* Start multitasking (i.e. give control to uC/OS-III). */

    while (DEF_ON) {
        ;
    }
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  StartupTask (void  *p_arg)
{
    OS_ERR       os_err;
#if (APP_CFG_TCPIP_EN > 0u)
    CPU_BOOLEAN  status;
#endif


   (void)p_arg;

    OS_TRACE_INIT();

    BSP_OS_TickEnable();                                        /* Enable the tick timer and interrupt                  */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&os_err);                            /* Compute CPU capacity with no task running            */
#endif

#if (APP_CFG_TCPIP_EN > 0u)
    status = AppTCPIP_Init();
    if (status != DEF_OK) {
        APP_TRACE_INFO(("uC/TCP-IP did not initialize properly.\n\r"));
        while (1);
    }
#endif

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        OSTimeDlyHMSM(0u, 0u, 1u, 0u,
                      OS_OPT_TIME_HMSM_STRICT,
                     &os_err);
    }
}
