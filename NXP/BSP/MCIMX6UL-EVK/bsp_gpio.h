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
* Filename : bsp_gpio.h
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

#ifndef  BSP_GPIO_PRESENT                                       /* See Note #1.                                         */
#define  BSP_GPIO_PRESENT


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

#define  BSP_GPIO_DIR_OUT           1u
#define  BSP_GPIO_DIR_IN            0u

#define  BSP_GPIO_LOW               0u
#define  BSP_GPIO_HIGH              1u

extern volatile char _gpio1_start;

#define  BSP_GPIO_1_BASE_ADDR       ((CPU_ADDR)(&_gpio1_start))

extern volatile char _gpio2_start;

#define  BSP_GPIO_2_BASE_ADDR       ((CPU_ADDR)(&_gpio2_start))

extern volatile char _gpio3_start;

#define  BSP_GPIO_3_BASE_ADDR       ((CPU_ADDR)(&_gpio3_start))

extern volatile char _gpio4_start;

#define  BSP_GPIO_4_BASE_ADDR       ((CPU_ADDR)(&_gpio4_start))

extern volatile char _gpio5_start;

#define  BSP_GPIO_5_BASE_ADDR       ((CPU_ADDR)(&_gpio5_start))

extern volatile char _gpio6_start;

#define  BSP_GPIO_6_BASE_ADDR       ((CPU_ADDR)(&_gpio6_start))

extern volatile char _gpio7_start;

#define  BSP_GPIO_7_BASE_ADDR       ((CPU_ADDR)(&_gpio7_start))

#define  BSP_GPIO_PIN_04            4u


#define  BSP_GPIO_ENET_MDIO_PIN     22u
#define  BSP_GPIO_ENET_REF_CLK      23u
#define  BSP_GPIO_ENET_RX_ER        24u
#define  BSP_GPIO_ENET_CRS_DV       25u
#define  BSP_GPIO_ENET_RXD1         26u
#define  BSP_GPIO_ENET_RXD0         27u
#define  BSP_GPIO_ENET_TX_EN        28u
#define  BSP_GPIO_ENET_TXD1         29u
#define  BSP_GPIO_ENET_TXD0         30u
#define  BSP_GPIO_ENET_MDC          31u


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

typedef  struct  _bsp_gpio_map {
    CPU_REG32    Data;
    CPU_REG32    Dir;
    CPU_REG32    Status;
    CPU_REG32    IntCfg1;
    CPU_REG32    IntCfg2;
    CPU_REG32    IntMask;
    CPU_REG32    IntStatus;
    CPU_REG32    EdgeSel;
} BSP_GPIO_MAP;


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

void  BSP_GPIO_SetDir(CPU_ADDR    base,
                      CPU_INT08U  pin,
                      CPU_INT08U  dir);

void  BSP_GPIO_Wr    (CPU_ADDR    base,
                      CPU_INT08U  pin,
                      CPU_INT08U  val);


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
