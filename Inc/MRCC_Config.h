/******************************************************/
/* SWC: RCC Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of RCC            */
/******************************************************/
/* Header File Guard */
#ifndef _MRCC_CONFIG_H_
#define _MRCC_CONFIG_H_

/* System CLK */
#define MRCC_SYSTEM_CLOCK_SOURCE		MRCC_HSI_CLK_SOURCE
/* Prescaler of AHB1/AHB2 Bus (SYSTEM_CLOCK/PRESCALER) */
#define MRCC_AHB_PRESCALER				MRCC_AHB_PRESCALE_BY_002
/* Prescaler of APB1 Bus (AHB1_CLOCK/PRESCALER) */
#define MRCC_APB1_PRESCALER				MRCC_APB_PRESCALE_BY_01
/* Prescaler of APB2 Bus (AHB1_CLOCK/PRESCALER) */
#define MRCC_APB2_PRESCALER				MRCC_APB_PRESCALE_BY_01
/* Trimming Value of HSI CLK */
#define MRCC_HSI_TRIMMING				0b10000
/* PLL P Division Factor */
#define MRCC_PLL_P_DIV_FACTOR			MRCC_PLLP_VALUE_2
/* PLL N Multiplication Factor */
#define MRCC_PLL_N_MUL_FACTOR			200
/* PLL M Division Factor */
#define MRCC_PLL_M_DIV_FACTOR			2

#endif /* _MRCC_CONFIG_H_ */
