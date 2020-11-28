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
*                                     MICRIUM BOARD SUPPORT PACKAGE
*                                CORTEX A7 GENERIC INTERRUPT CONTROLLER
*
* Filename : bsp_int_armv7a_gicv2.c
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#define    BSP_INT_MODULE

#include  <cpu.h>
#include  <lib_def.h>

#include  "bsp_int.h"
#include  "bsp_sys.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_INT_GIC_DIST_REG         ((ARM_REG_GIC_DIST_PTR)(BSP_SYS_ARM_MP_BASE_ADDR + 0x1000u))
#define  BSP_INT_GIC_IF_REG           ((ARM_REG_GIC_IF_PTR)(BSP_SYS_ARM_MP_BASE_ADDR   + 0x2000u))

                                                                /* ----------- DISTRIBUTOR CONTROL REGISTER ----------- */
#define  ARM_BIT_GIC_DIST_ICDDCR_EN            DEF_BIT_00       /* Global GIC enable.                                   */

                                                                /* ---------- CPU_INTERFACE_CONTROL_REGISTER ---------- */
#define  ARM_BIT_GIC_IF_ICCICR_ENS             DEF_BIT_00       /* Enable secure interrupts.                            */
#define  ARM_BIT_GIC_IF_ICCICR_ENNS            DEF_BIT_01       /* Enable non-secure interrupts.                        */
#define  ARM_BIT_GIC_IF_ICCICR_ACKCTL          DEF_BIT_02       /* Secure ack of NS interrupts.                         */


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

static  BSP_INT_FNCT_PTR  BSP_IntVectTbl[BSP_INT_SRC_MAX];      /* Interrupt vector table.                              */


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*
* Note(s) : 1) Register Descriptions can be found in "Cortex-A7 MPCore Technical Reference Manual", and
*              "ARM Generic Interrupt Controller Architecture Specification".
*
*********************************************************************************************************
*/


CPU_INT32U  GIC_IntNum;


typedef  struct  arm_reg_gic_dist { 
    CPU_INT32U  GICD_CTLR;                                      /* 0x1000 Distributor Control Register                  */
    CPU_INT32U  GICD_TYPER;                                     /* 0x1004 Interrupt Controller Type Register            */
    CPU_INT32U  GICD_IIDR;                                      /* 0x1008 Distributor Implementer ID Register           */
    CPU_INT32U  RESERVED1[29u];
    CPU_INT32U  GICD_IGROUPR[16u];                              /* 0x1080 - 0x0BC Interrupt Group Registers             */
    CPU_INT32U  RESERVED2[16u];
    CPU_INT32U  GICD_ISENABLER[16u];                            /* 0x1100 - 0x13C Interrupt Set-Enable Registers        */
    CPU_INT32U  RESERVED3[16u];
    CPU_INT32U  GICD_ICENABLER[16u];                            /* 0x1180 - 0x1BC Interrupt Clear-Enable Registers      */
    CPU_INT32U  RESERVED4[16u];
    CPU_INT32U  GICD_ISPENDR[16u];                              /* 0x1200 - 0x23C Interrupt Set-Pending Registers       */
    CPU_INT32U  RESERVED5[16u];
    CPU_INT32U  GICD_ICPENDR[16u];                              /* 0x1280 - 0x2BC Interrupt Clear-Pending Registers     */
    CPU_INT32U  RESERVED6[16u];
    CPU_INT32U  GICD_ISACTIVER[16u];                            /* 0x1300 - 0x33C Interrupt Set-Active Registers        */
    CPU_INT32U  RESERVED7[16u];
    CPU_INT32U  GICD_ICACTIVER[16u];                            /* 0x1380 - 0x3BC Interrupt Clear-Active Registers      */
    CPU_INT32U  RESERVED8[16u];
    CPU_INT08U  GICD_IPRIORITYR[512u];                          /* 0x1400 - 0x5FC Interrupt Priority Registers          */
    CPU_INT32U  RESERVED9[128u];
    CPU_INT08U  GICD_ITARGETSR[512u];                           /* 0x1800 - 0x9FC Interrupt Targets Registers           */
    CPU_INT32U  RESERVED10[128u];
    CPU_INT32U  GICD_ICFGR[32u];                                /* 0x1C00 - 0xC7C Interrupt configuration registers     */
    CPU_INT32U  RESERVED11[32u];
    CPU_INT32U  GICD_PPISR;                                     /* 0x1D00   Private Peripheral Interrupt Status Reg.    */
    CPU_INT32U  GICD_SPISR[15u];                                /* 0x1D04 - 0xD3C Shared Periph. Interrupt Status Regs. */
    CPU_INT32U  RESERVED12[112u];
    CPU_INT32U  GICD_SGIR;                                      /* 0x1F00   Software Generated Interrupt Register       */
    CPU_INT32U  RESERVED13[3u];
    CPU_INT08U  GICD_CPENDSGIR[16u];                            /* 0x1F10 - 0xF1C (R/W) SGI Clear-Pending Registers     */
    CPU_INT08U  GICD_SPENDSGIR[16u];                            /* 0x1F20 - 0xF2C (R/W) SGI Set-Pending Registers       */
    CPU_INT32U  RESERVED14[40u];
    CPU_INT32U  GICD_PIDR4;                                     /* 0x1FD0  Peripheral ID4 Register                      */
    CPU_INT32U  GICD_PIDR5;                                     /* 0x1FD4  Peripheral ID5 Register                      */
    CPU_INT32U  GICD_PIDR6;                                     /* 0x1FD8  Peripheral ID6 Register                      */
    CPU_INT32U  GICD_PIDR7;                                     /* 0x1FDC  Peripheral ID7 Register                      */
    CPU_INT32U  GICD_PIDR0;                                     /* 0x1FE0  Peripheral ID0 Register                      */
    CPU_INT32U  GICD_PIDR1;                                     /* 0x1FE4  Peripheral ID1 Register                      */
    CPU_INT32U  GICD_PIDR2;                                     /* 0x1FE8  Peripheral ID2 Register                      */
    CPU_INT32U  GICD_PIDR3;                                     /* 0x1FEC  Peripheral ID3 Register                      */
    CPU_INT32U  GICD_CIDR0;                                     /* 0x1FF0  Component ID0 Register                       */
    CPU_INT32U  GICD_CIDR1;                                     /* 0x1FF4  Component ID1 Register                       */
    CPU_INT32U  GICD_CIDR2;                                     /* 0x1FF8  Component ID2 Register                       */
    CPU_INT32U  GICD_CIDR3;                                     /* 0x1FFC  Component ID3 Register                       */
} ARM_REG_GIC_DIST, *ARM_REG_GIC_DIST_PTR;

typedef  struct  arm_reg_gic_if {
    CPU_INT32U  GIC_CTLR;                                       /* 0x2000 CPU Interface Control Register                */
    CPU_INT32U  GIC_PMR;                                        /* 0x2004 Interrupt Priority Mask Register              */
    CPU_INT32U  GIC_BPR;                                        /* 0x2008 Binary Point Register                         */
    CPU_INT32U  GIC_IAR;                                        /* 0x200C Interrupt Acknowledge Register                */
    CPU_INT32U  GIC_EOIR;                                       /* 0x2010 End Of Interrupt Register                     */
    CPU_INT32U  GIC_RPR;                                        /* 0x2014 Running Priority Register                     */
    CPU_INT32U  GIC_HPPIR;                                      /* 0x2018 Highest Priority Pending Interrupt Register   */
    CPU_INT32U  GIC_ABPR;                                       /* 0x201C Aliased Binary Point Register                 */
    CPU_INT32U  GIC_AIAR;                                       /* 0x2020 Aliased Interrupt Acknowledge Register        */
    CPU_INT32U  GIC_AEOIR;                                      /* 0x2024 Aliased End Of Interrupt Register             */
    CPU_INT32U  GIC_AHPPIR;                                     /* 0x2028 Aliased Highest Prio Pending Interrupt Reg.   */
    CPU_INT32U  RESERVED15[41u];
    CPU_INT32U  GIC_APR0;                                       /* 0x20D0 Active Priority Register                      */
    CPU_INT32U  RESERVED16[3u];
    CPU_INT32U  GIC_NSAPR0;                                     /* 0x20E0 Non-secure Active Priority Register           */
    CPU_INT32U  RESERVED17[6u];
    CPU_INT32U  GIC_IIDR;                                       /* 0x20FC CPU Interface Identification Register         */
    CPU_INT32U  RESERVED18[960u];
    CPU_INT32U  GIC_DIR;                                        /* 0x3000 Deactivate Interrupt Register                 */
} ARM_REG_GIC_IF, *ARM_REG_GIC_IF_PTR;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            BSP_IntInit()
*
* Description : Initialize interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void BSP_IntInit (void)
{
    CPU_INT32U  it_lines_num;
    CPU_INT32U  i;

                                                                
    BSP_INT_GIC_DIST_REG->GICD_CTLR = 0u;                       /* Disable interrupts from the GIC Distributor.         */
                                                                
    BSP_INT_GIC_IF_REG->GIC_CTLR    = 0u;                       /* Disable interrupt signaling from GIC CPU interface.  */
                                                                /* Determine the nunber of interrupts the GIC supports. */
    it_lines_num = (BSP_INT_GIC_DIST_REG->GICD_TYPER & 0x1Fu) + 1u; 
    GIC_IntNum   = it_lines_num * 32u; 

                                                                /* Disable all SPI interrupts.                          */
    for (i = 1u; it_lines_num > i; i++ ) {
        BSP_INT_GIC_DIST_REG->GICD_ICENABLER[i] = DEF_INT_32U_MAX_VAL;
    }
                                                                
    BSP_INT_GIC_IF_REG->GIC_PMR     = 0xFFu;                    /* Cfg. Interrupt Priority Mask Reg. Don't filter int's.*/
    BSP_INT_GIC_IF_REG->GIC_BPR     = 0u;                       /* Set Binary Point.                                    */
    BSP_INT_GIC_IF_REG->GIC_CTLR    = 1u;                       /* Enable interrupt signaling from the CPU Interface.   */
    BSP_INT_GIC_DIST_REG->GICD_CTLR = 1u;                       /* Enable interrupts on the GIC Distributor.            */
}


/*
*********************************************************************************************************
*                                            BSP_IntSrcEn()
*
* Description : Enable interrupt source int_id.
*
* Argument(s) : int_id		Interrupt to enable.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntSrcEn (CPU_INT32U int_id)
{
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_bit;


    if(int_id >= BSP_INT_SRC_MAX) {
        return;
    }

    CPU_MB();
    reg_off = (int_id >>    5u);                                /* Calculate the register offset.                       */
    reg_bit = (int_id &  0x1Fu);                                /* Mask bit ID.                                         */

    BSP_INT_GIC_DIST_REG->GICD_ISENABLER[reg_off] = (1u << reg_bit);
    CPU_MB();
}


/*
*********************************************************************************************************
*                                            BSP_IntSrcDis()
*
* Description : Disable interrupt source int_id.
*
* Argument(s) : int_id  	Interrupt to disable.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntSrcDis (CPU_INT32U int_id)
{
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_bit;


    if (int_id >= BSP_INT_SRC_MAX) {
        return;
    }

    CPU_MB();
    reg_off = (int_id >>    5u);                                /* Calculate the register offset.                       */
    reg_bit = (int_id &  0x1Fu);                                /* Mask bit ID.                                         */
    BSP_INT_GIC_DIST_REG->GICD_ICENABLER[reg_off] = 1u << reg_bit;
    CPU_MB();
}


/*
*********************************************************************************************************
*                                         BSP_IntPrioMaskSet()
*
* Description : Set CPU's interrupt priority mask.
*
* Argument(s) : prio    	Priority mask.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntPrioMaskSet (CPU_INT32U prio)
{
    if (prio < BSP_INT_PRIO_LVL_MAX) {
        CPU_MB();
        BSP_INT_GIC_IF_REG->GIC_PMR = prio;
        CPU_MB();
    }
}


/*
*********************************************************************************************************
*                                           BSP_IntPrioSet()
*
* Description : Set interrupt priority.
*
* Argument(s) : int_id  Interrupt id.
*
*               prio    Interrupt priority.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntPrioSet (CPU_INT32U  int_id,
                      CPU_INT32U  prio)
{
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_byte;
    CPU_INT32U  temp_reg;
    CPU_SR_ALLOC();


    if (int_id >= BSP_INT_SRC_MAX) {
        return;
    }

    if (prio >= BSP_INT_PRIO_LVL_MAX) {
        return;
    }

    CPU_CRITICAL_ENTER();
    reg_off  = (int_id >>    2u);
    reg_byte = (int_id &  0x03u);
    
    temp_reg =  BSP_INT_GIC_DIST_REG->GICD_IPRIORITYR[reg_off];
    temp_reg = (temp_reg & ~(0xFF << (reg_byte * 8u)));
    temp_reg = (temp_reg | ((prio & 0x1Fu) << (reg_byte * 8u)));
    
    BSP_INT_GIC_DIST_REG->GICD_IPRIORITYR[reg_off] = temp_reg;
    CPU_CRITICAL_EXIT();
}


/*
*********************************************************************************************************
*                                          BSP_IntTargetSet()
*
* Description : Set interrupt target.
*
* Argument(s) : int_id              Interrupt id.
*
*               int_target_list     Interrupt CPU target list.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntTargetSet (CPU_INT32U  int_id,
                        CPU_INT08U  int_target_list)
{
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_byte;
    CPU_INT32U  temp_reg;
    CPU_SR_ALLOC();


    if(int_id >= BSP_INT_SRC_MAX) {
        return;
    }

    CPU_CRITICAL_ENTER();
    reg_off  = (int_id >>    2u);
    reg_byte = (int_id &  0x03u);

    temp_reg =  BSP_INT_GIC_DIST_REG->GICD_ITARGETSR[reg_off];
    temp_reg = (temp_reg & ~(0xFF << (reg_byte * 8u)));
    temp_reg = (temp_reg | ((int_target_list & 0x1Fu) << (reg_byte * 8u)));

    BSP_INT_GIC_DIST_REG->GICD_ITARGETSR[reg_off] = temp_reg;
    CPU_CRITICAL_EXIT();
}


/*
*********************************************************************************************************
*                                           BSP_IntVectSet()
*
* Description : Configure interrupt vector.
*
* Argument(s) : int_id              Interrupt ID.
*
*               int_prio            Interrupt priority.
*
*               int_target_list     Interrupt CPU target list
*
*               int_fnct            ISR function pointer.
*
* Return(s)   : Interrupt configuration result.
*                                DEF_YES    Interrupt successfully set.
*                                DEF_NO     Error setting interrupt.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_IntVectSet (CPU_INT32U        int_id,
                             CPU_INT32U        int_prio,
                             CPU_INT08U        int_target_list,
                             BSP_INT_FNCT_PTR  int_fnct)
{
    CPU_SR_ALLOC();


    if (int_prio > BSP_INT_PRIO_LVL_MAX) {
        return (DEF_NO);
    }

    if (int_id > BSP_INT_SRC_MAX) {
        return (DEF_NO);
    }

#if 0
    if (int_target_list > 255u) {
        return (DEF_NO);
    }
#endif

    BSP_IntPrioSet  (int_id, int_prio);
    BSP_IntTargetSet(int_id, int_target_list);

    CPU_CRITICAL_ENTER();                                       /* Prevent partially configured interrupts.             */
    BSP_IntVectTbl[int_id] = int_fnct;
    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                           BSP_IntHandler()
*
* Description : Generic interrupt handler.
*
* Argument(s) : Interrupt type.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntHandler (void)
{
    CPU_INT32U        int_ack;
    CPU_INT32U        int_id;
    CPU_INT32U        int_cpu;
    BSP_INT_FNCT_PTR  p_isr;


    int_ack = BSP_INT_GIC_IF_REG->GIC_IAR;
    int_id  = int_ack & DEF_BIT_FIELD(10u, 0u);                 /* Mask away the CPUID.                                 */

    if (int_id == 1023u) {                                      /* Spurious interrupt.                                  */
        return;
    }

    int_cpu = (int_ack & DEF_BIT_FIELD(12u, 2u)) >> 10u;        /* Extract the interrupt source.                        */

    p_isr   = BSP_IntVectTbl[int_id];                           /* Fetch ISR handler.                                   */

    if (p_isr != DEF_NULL) {
       (*p_isr)(int_cpu);                                       /* Call ISR handler.                                    */
    }

    CPU_MB();                                                   /* Memory barrier before ending the interrupt.          */

    BSP_INT_GIC_IF_REG->GIC_EOIR = int_ack;
}
