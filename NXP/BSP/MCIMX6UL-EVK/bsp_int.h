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
* Filename : bsp_int.h
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This BSP interrupt header file is protected from multiple pre-processor inclusion through
*               use of the BSP interrupt present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_INT_PRESENT                                        /* See Note #1.                                         */
#define  BSP_INT_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>


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

#ifdef   BSP_INT_MODULE
#define  BSP_INT_EXT
#else
#define  BSP_INT_EXT  extern
#endif


/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DEFINES
* Note(s) : (1) The first 32 interrupts are private to the CPU architecture
*********************************************************************************************************
*/

typedef  void  (*BSP_INT_FNCT_PTR)(CPU_INT32U  cpu);

                                                                /* ------------- INTERRUPT PRIORITY LEVEL ------------- */
#define  BSP_INT_PRIO_LVL_MAX                 256u

                                                                /* --------------- RESERVED INTERRUPTs ---------------- */
                                                                /* See note 1.                                          */
#define  BSP_INT_SRC_RSDV_00                    0u              
#define  BSP_INT_SRC_RSDV_01                    1u              
#define  BSP_INT_SRC_RSDV_02                    2u              
#define  BSP_INT_SRC_RSDV_03                    3u              
#define  BSP_INT_SRC_RSDV_04                    4u              
#define  BSP_INT_SRC_RSDV_05                    5u              
#define  BSP_INT_SRC_RSDV_06                    6u              
#define  BSP_INT_SRC_RSDV_07                    7u              
#define  BSP_INT_SRC_RSDV_08                    8u              
#define  BSP_INT_SRC_RSDV_09                    9u              
#define  BSP_INT_SRC_RSDV_10                   10u              
#define  BSP_INT_SRC_RSDV_11                   11u              
#define  BSP_INT_SRC_RSDV_12                   12u              
#define  BSP_INT_SRC_RSDV_13                   13u              
#define  BSP_INT_SRC_RSDV_14                   14u              
#define  BSP_INT_SRC_RSDV_15                   15u              
#define  BSP_INT_SRC_RSDV_16                   16u
#define  BSP_INT_SRC_RSDV_17                   17u
#define  BSP_INT_SRC_RSDV_18                   18u
#define  BSP_INT_SRC_RSDV_19                   19u
#define  BSP_INT_SRC_RSDV_20                   20u
#define  BSP_INT_SRC_RSDV_21                   21u
#define  BSP_INT_SRC_RSDV_22                   22u
#define  BSP_INT_SRC_RSDV_23                   23u
#define  BSP_INT_SRC_RSDV_24                   24u
#define  BSP_INT_SRC_RSDV_25                   25u
#define  BSP_INT_SRC_RSDV_26                   26u
#define  BSP_INT_SRC_RSDV_27                   27u
#define  BSP_INT_SRC_RSDV_28                   28u
#define  BSP_INT_SRC_RSDV_29                   29u
#define  BSP_INT_SRC_RSDV_30                   30u
#define  BSP_INT_SRC_RSDV_31                   31u
                                                                /* ---------------- EXTERNAL INTERRUPTs --------------- */
#define  BSP_INT_SRC_IOMUXC                    32u              /* GPR 1 from IOMUXC. Notifies on except cond on boot.  */
#define  BSP_INT_SRC_DAP                       33u              /* Debug Access Point Interrupt Request.                */
#define  BSP_INT_SRC_SDMA                      34u              /* SDMA Interrupt Request from all channels.            */
#define  BSP_INT_SRC_TSC                       35u              /* TSC Interrupt.                                       */
#define  BSP_INT_SRC_SNVS_LP_HP                36u              /* Logic OR of SNVS_LP and SNVS_HP.                     */
#define  BSP_INT_SRC_LCDIF                     37u              /* LCDIF Sync Interrupt.                                */
#define  BSP_INT_SRC_BEE                       38u              /* BEE Interrupt.                                       */
#define  BSP_INT_SRC_CSI                       39u              /* CMOS Sensor Interface Interrupt Request.             */
#define  BSP_INT_SRC_PXP                       40u              /* PXP Interrupt.                                       */
#define  BSP_INT_SRC_SCTR1                     41u              /* SCTR Compare Interrupt Request.                      */
#define  BSP_INT_SRC_SCTR2                     42u              /* SCTR Compare Interrupt Request.                      */
#define  BSP_INT_SRC_WDOG3                     43u              /* WDOG3 Watchdog Timer Reset Interrupt Request.        */
#define  BSP_INT_SRC_RSDV32                    44u              /* Reserved.                                            */
#define  BSP_INT_SRC_APBH_DMA                  45u              /* Logic OR of APBH DMA Channels 0-3 Complete & Err Int.*/
#define  BSP_INT_SRC_WEIM                      46u              /* WEIM Interrupt Request.                              */
#define  BSP_INT_SRC_BCH                       47u              /* RAWNAND BCH Operation Complete Error Interrupt.      */
#define  BSP_INT_SRC_GPMI                      48u              /* RAWNAND GPMI Operation Timeout Error Interrupt.      */
#define  BSP_INT_SRC_UART6                     49u              /* UART6 Interrupt Request.                             */
#define  BSP_INT_SRC_RSVD33                    50u              /* Reserved.                                            */
#define  BSP_INT_SRC_SNVS_CONSOLIDATE          51u              /* SNVS Consolidated Interrupt.                         */
#define  BSP_INT_SRC_SNVS_SECURITY             52u              /* SNVS Security Interrupt.                             */
#define  BSP_INT_SRC_CSU                       53u              /* Tells MCU that 1 or more alarms inputs were asserted.*/
#define  BSP_INT_SRC_USDHC1                    54u              /* uSDHC1 (Enhanced SDHC) Interrupt Request.            */
#define  BSP_INT_SRC_USDHC2                    55u              /* uSDHC2 (Enhanced SDHC) Interrupt Request.            */
#define  BSP_INT_SRC_SAI3_RX                   56u              /* SAI3 (Serial Audio Interface) Interrupt Request.     */
#define  BSP_INT_SRC_SAI3_TX                   57u              /* SAI3 (Serial Audio Interface) Interrupt Request.     */
#define  BSP_INT_SRC_UART1                     58u              /* UART1 Interrupt Request.                             */
#define  BSP_INT_SRC_UART2                     59u              /* UART2 Interrupt Request.                             */
#define  BSP_INT_SRC_UART3                     60u              /* UART3 Interrupt Request.                             */
#define  BSP_INT_SRC_UART4                     61u              /* UART4 Interrupt Request.                             */
#define  BSP_INT_SRC_UART5                     62u              /* UART5 Interrupt Request.                             */
#define  BSP_INT_SRC_ECSP1                     63u              /* eCSP1 Interrupt Request.                             */
#define  BSP_INT_SRC_ECSP2                     64u              /* eCSP2 Interrupt Request.                             */
#define  BSP_INT_SRC_ECSP3                     65u              /* eCSP3 Interrupt Request.                             */
#define  BSP_INT_SRC_ECSP4                     66u              /* eCSP4 Interrupt Request.                             */
#define  BSP_INT_SRC_I2C4                      67u              /* I2C4 Interrupt Request.                              */
#define  BSP_INT_SRC_I2C1                      68u              /* I2C1 Interrupt Request.                              */
#define  BSP_INT_SRC_I2C2                      69u              /* I2C2 Interrupt Request.                              */
#define  BSP_INT_SRC_I2C3                      70u              /* I2C3 Interrupt Request.                              */
#define  BSP_INT_SRC_UART7                     71u              /* UART7 ORed Interrupt.                                */
#define  BSP_INT_SRC_UART8                     72u              /* UART8 ORed Interrupt.                                */
#define  BSP_INT_SRC_USB_RSVD34                73u              /* Reserved.                                            */
#define  BSP_INT_SRC_USB_OTG2                  74u              /* USB OTG2 Interrupt Request.                          */
#define  BSP_INT_SRC_USB_OTG1                  75u              /* USB OTG1 Interrupt Request.                          */
#define  BSP_INT_SRC_USB_PHY_UTMI0             76u              /* UTMI0 Interrupt Request.                             */
#define  BSP_INT_SRC_USB_PHY_UTMI1             77u              /* UTMI1 Interrupt Request.                             */
#define  BSP_INT_SRC_CAAM_JQ2                  78u              /* CAAM Interrupt Queue for JQ2.                        */
#define  BSP_INT_SRC_CAAM_ERR                  79u              /* CAAM Interrupt for Recoverable Error.                */
#define  BSP_INT_SRC_CAAM_RTIC                 80u              /* CAAM Interrupt for RTIC.                             */
#define  BSP_INT_SRC_TMP_MONITOR               81u              /* Temperature Sensor (temp.> threshold) intr. request. */
#define  BSP_INT_SRC_ASRC                      82u              /* ASRC Interrupt Request.                              */
#define  BSP_INT_SRC_RSVD35                    83u              /* Reserved.                                            */
#define  BSP_INT_SRC_SPDIF                     84u              /* SPDIF Interrupt.                                     */
#define  BSP_INT_SRC_RSVD36                    85u              /* Reserved.                                            */
#define  BSP_INT_SRC_PMU1                      86u              /* Brownout event on either the 1.1, 2.5 or 3.0 regul.  */
#define  BSP_INT_SRC_GPT1                      87u              /* Logical OR of GPT1 rollover int. line, input capt... */
                                                                /* ...1&2 lines, output comp 1,2&3 interrupt lines.     */
#define  BSP_INT_SRC_EPIT1                     88u              /* EPIT1 Output Compare Interrupt.                      */
#define  BSP_INT_SRC_EPIT2                     89u              /* EPIT2 Output Compare Interrupt.                      */
#define  BSP_INT_SRC_GPIO1_INT7                90u              /* INT7 Interrupt Request.                              */
#define  BSP_INT_SRC_GPIO1_INT6                91u              /* INT6 Interrupt Request.                              */
#define  BSP_INT_SRC_GPIO1_INT5                92u              /* INT5 Interrupt Request.                              */
#define  BSP_INT_SRC_GPIO1_INT4                93u              /* INT4 Interrupt Request.                              */
#define  BSP_INT_SRC_GPIO1_INT3                94u              /* INT3 Interrupt Request.                              */
#define  BSP_INT_SRC_GPIO1_INT2                95u              /* INT2 Interrupt Request.                              */
#define  BSP_INT_SRC_GPIO1_INT1                96u              /* INT1 Interrupt Request.                              */
#define  BSP_INT_SRC_GPIO1_INT0                97u              /* INT0 Interrupt Request.                              */
#define  BSP_INT_SRC_GPIO1_SIG_00_15           98u              /* Combined Intr. Indication GPIO1 signals  0-15.       */
#define  BSP_INT_SRC_GPIO1_SIG_16_31           99u              /* Combined Intr. Indication GPIO1 signals 16-31.       */
#define  BSP_INT_SRC_GPIO2_SIG_00_15          100u              /* Combined Intr. Indication GPIO2 signals  0-15.       */
#define  BSP_INT_SRC_GPIO2_SIG_16_31          101u              /* Combined Intr. Indication GPIO2 signals 16-31.       */
#define  BSP_INT_SRC_GPIO3_SIG_00_15          102u              /* Combined Intr. Indication GPIO3 signals  0-15.       */
#define  BSP_INT_SRC_GPIO3_SIG_16_31          103u              /* Combined Intr. Indication GPIO3 signals 16-31.       */
#define  BSP_INT_SRC_GPIO4_SIG_00_15          104u              /* Combined Intr. Indication GPIO4 signals  0-15.       */
#define  BSP_INT_SRC_GPIO4_SIG_16_31          105u              /* Combined Intr. Indication GPIO4 signals 16-31.       */
#define  BSP_INT_SRC_GPIO5_SIG_00_15          106u              /* Combined Intr. Indication GPIO5 signals  0-15.       */
#define  BSP_INT_SRC_GPIO5_SIG_16_31          107u              /* Combined Intr. Indication GPIO5 signals 16-31.       */
#define  BSP_INT_SRC_RSVD37                   108u              /* Reserved.                                            */
#define  BSP_INT_SRC_RSVD38                   109u              /* Reserved.                                            */
#define  BSP_INT_SRC_RSVD39                   110u              /* Reserved.                                            */
#define  BSP_INT_SRC_RSVD40                   111u              /* Reserved.                                            */
#define  BSP_INT_SRC_WDOG1                    112u              /* WDOG1 Timer Reset Interrupt Request.                 */
#define  BSP_INT_SRC_WDOG2                    113u              /* WDOG2 Timer Reset Interrupt Request.                 */
#define  BSP_INT_SRC_KPP                      114u              /* Key Pad Interrupt Request.                           */
#define  BSP_INT_SRC_PWM1                     115u              /* Cumulative Intr. Line PWM1. Logical OR of rollover.. */
                                                                /* ..compare, and FIFO waterlevel crossing intr.        */
#define  BSP_INT_SRC_PWM2                     116u              /* Cumulative Intr. Line PWM2. Logical OR of rollover.. */
                                                                /* ..compare, and FIFO waterlevel crossing intr.        */
#define  BSP_INT_SRC_PWM3                     117u              /* Cumulative Intr. Line PWM3. Logical OR of rollover.. */
                                                                /* ..compare, and FIFO waterlevel crossing intr.        */
#define  BSP_INT_SRC_PWM4                     118u              /* Cumulative Intr. Line PWM4. Logical OR of rollover.. */
                                                                /* ..compare, and FIFO waterlevel crossing intr.        */
#define  BSP_INT_SRC_CCM_INT1                 119u              /* CCM Interrupt Request 1.                             */
#define  BSP_INT_SRC_CCM_INT2                 120u              /* CCM Interrupt Request 2.                             */
#define  BSP_INT_SRC_GPC_INT1                 121u              /* GPC Interrupt Request 1.                             */
#define  BSP_INT_SRC_RSVD_41                  122u              /* Reserved.                                            */
#define  BSP_INT_SRC_SRC                      123u              /* SRC Interrupt Request.                               */
#define  BSP_INT_SRC_RSVD42                   124u              /* Reserved.                                            */
#define  BSP_INT_SRC_RSVD43                   125u              /* Reserved.                                            */
#define  BSP_INT_SRC_CPU_PERFORM              126u              /* CPU Performance Unit Interrupt.                      */
#define  BSP_INT_SRC_CPU_TRIGGER              127u              /* CPU CTI Trigger Outputs Interrupt.                   */
#define  BSP_INT_SRC_SRC_COMB_WDOG            128u              /* Combined CPU WDOG Interrupts (4x) out of SRC.        */
#define  BSP_INT_SRC_SAI1                     129u              /* SAI1 (Serial Audio Interface) Interrupt Request.     */
#define  BSP_INT_SRC_SAI2                     130u              /* SAI2 (Serial Audio Interface) Interrupt Request.     */
#define  BSP_INT_SRC_RSVD_44                  131u              /* Reserved.                                            */
#define  BSP_INT_SRC_ADC1                     132u              /* ADC Interrupt Request 1.                             */
#define  BSP_INT_SRC_ADC2                     133u              /* ADC Interrupt Request 2.                             */
#define  BSP_INT_SRC_RSVD_45                  134u              /* Reserved.                                            */
#define  BSP_INT_SRC_RSVD_46                  135u              /* Reserved.                                            */
#define  BSP_INT_SRC_SJC                      136u              /* SJC Interrupt from General Purpose Register.         */
#define  BSP_INT_SRC_CAAM_RING0               137u              /* CAAM Job Ring 0 Interrupt.                           */
#define  BSP_INT_SRC_CAAM_RING1               138u              /* CAAM Job Ring 1 Interrupt.                           */
#define  BSP_INT_SRC_QSPI                     139u              /* QSPI Interrupt Request.                              */
#define  BSP_INT_SRC_TZASC                    140u              /* TZASC1 Interrupt Request.                            */
#define  BSP_INT_SRC_GPT2                     141u              /* Logical OR of GPT2 rollover int. line, input capt... */
                                                                /* ...1&2 lines, output comp 1,2&3 interrupt lines.     */
#define  BSP_INT_SRC_CAN1                     142u              /* CAN1 Combined Interrupt. BUSOFF, ERROR, MBOR, ...    */
                                                                /* ... TX WARNING, & WAKEN Interrupts.                  */
#define  BSP_INT_SRC_CAN2                     143u              /* CAN2 Combined Interrupt. BUSOFF, ERROR, MBOR, ...    */
                                                                /* ... TX WARNING, & WAKEN Interrupts.                  */
#define  BSP_INT_SRC_SIM1                     144u              /* SIM1 Interrupt Request.                              */
#define  BSP_INT_SRC_SIM2                     145u              /* SIM2 Interrupt Request.                              */
#define  BSP_INT_SRC_PWM5                     146u              /* Cumulative Intr. Line PWM5. Logical OR of rollover.. */
                                                                /* ..compare, and FIFO waterlevel crossing intr.        */
#define  BSP_INT_SRC_PWM6                     147u              /* Cumulative Intr. Line PWM6. Logical OR of rollover.. */
                                                                /* ..compare, and FIFO waterlevel crossing intr.        */
#define  BSP_INT_SRC_PWM7                     148u              /* Cumulative Intr. Line PWM7. Logical OR of rollover.. */
                                                                /* ..compare, and FIFO waterlevel crossing intr.        */
#define  BSP_INT_SRC_PWM8                     149u              /* Cumulative Intr. Line PWM8. Logical OR of rollover.. */
                                                                /* ..compare, and FIFO waterlevel crossing intr.        */
#define  BSP_INT_SRC_ENET1                    150u              /* ENET1 Interrupt Request.                             */
#define  BSP_INT_SRC_ENET1_1588_TMR           151u              /* ENET1 1588 Timer Interrupt [Synchronous] Request.    */
#define  BSP_INT_SRC_ENET2                    152u              /* ENET2 Interrupt Request.                             */
#define  BSP_INT_SRC_ENET2_1588_TMR           153u              /* ENET2 1588 Timer Interrupt [Synchronous] Request.    */

#define  BSP_INT_SRC_RSVD_47                  154u              /* Reserved.                                            */
#define  BSP_INT_SRC_RSVD_48                  155u              /* Reserved.                                            */
#define  BSP_INT_SRC_RSVD_49                  156u              /* Reserved.                                            */
#define  BSP_INT_SRC_RSVD_50                  157u              /* Reserved.                                            */
#define  BSP_INT_SRC_RSVD_51                  158u              /* Reserved.                                            */
#define  BSP_INT_SRC_PMU2                     159u              /* PMU Brownout Event on the Core, GPU, or SoC Regulator*/

#define  BSP_INT_SRC_MAX                      160u


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
*                                              MACROS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_IntInit       (void);

void         BSP_IntSrcEn      (CPU_INT32U        int_id);

void         BSP_IntSrcDis     (CPU_INT32U        int_id);

void         BSP_IntPrioMaskSet(CPU_INT32U        prio);

void         BSP_IntTargetSet  (CPU_INT32U        int_id,
                                CPU_INT08U        int_target_list);

CPU_BOOLEAN  BSP_IntVectSet    (CPU_INT32U        int_id,
                                CPU_INT32U        int_prio,
                                CPU_INT08U        int_target_list,
                                BSP_INT_FNCT_PTR  int_fnct);

void         BSP_IntHandler    (void);


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
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
