/******************************************************/
/* SWC: STK Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of STK            */
/******************************************************/
/* Header File Guard */
#ifndef _MSTK_PRIVATE_H_
#define _MSTK_PRIVATE_H_

#define STK_CTRL                    *((volatile u32*)0xE000E010)
#define STK_LOAD                    *((volatile u32*)0xE000E014)
#define STK_VAL                     *((volatile u32*)0xE000E018)
#define STK_CALIB                   *((volatile u32*)0xE000E0C0)


/**********************************************/
/*                CLOCK SOURCES               */
/**********************************************/
#define MSTK_AHB_DIV_8				0
#define MSTK_AHB_NO_DIV				1

/**********************************************/
/*             HANDLER CALL MODES             */
/**********************************************/
#define MSTK_SINGLE_CALL_MODE		0
#define MSTK_PERIODIC_CALL_MODE		1


/**********************************************/
/*              CTRL BITS Mapping             */
/**********************************************/
#define MSTK_CTRL_ENABLE_BIT			0
#define MSTK_CTRL_TICKINT_BIT			1
#define MSTK_CTRL_CLKSOURCE_BIT			2
#define MSTK_CTRL_COUNTFLAG_BIT			16

#endif /* _MSTK_PRIVATE_H_ */
