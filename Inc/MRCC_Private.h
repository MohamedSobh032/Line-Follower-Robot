/******************************************************/
/* SWC: RCC Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of RCC            */
/******************************************************/
/* Header File Guard */
#ifndef _MRCC_PRIVATE_H_
#define _MRCC_PRIVATE_H_

/* RCC: Base Address: 0x40023800 */
#define MRCC_BASE_ADDRESS		 0x40023800

/**********************************************/
/*                RCC Registers               */
/**********************************************/
#define RCC_CR				 *((volatile u32*)(MRCC_BASE_ADDRESS+0x00))
#define RCC_PLLCFGR			 *((volatile u32*)(MRCC_BASE_ADDRESS+0x04))
#define RCC_CFGR			 *((volatile u32*)(MRCC_BASE_ADDRESS+0x08))
#define RCC_CIR				 *((volatile u32*)(MRCC_BASE_ADDRESS+0x0C))
#define RCC_AHB1ENR			 *((volatile u32*)(MRCC_BASE_ADDRESS+0x30))
#define RCC_AHB2ENR			 *((volatile u32*)(MRCC_BASE_ADDRESS+0x34))
#define RCC_APB1ENR			 *((volatile u32*)(MRCC_BASE_ADDRESS+0x40))
#define RCC_APB2ENR			 *((volatile u32*)(MRCC_BASE_ADDRESS+0x44))
#define RCC_AHB1LPENR	     *((volatile u32*)(MRCC_BASE_ADDRESS+0x50))
#define RCC_AHB2LPENR	     *((volatile u32*)(MRCC_BASE_ADDRESS+0x54))
#define RCC_APB1LPENR		 *((volatile u32*)(MRCC_BASE_ADDRESS+0x60))
#define RCC_APB2LPENR		 *((volatile u32*)(MRCC_BASE_ADDRESS+0x64))

/**********************************************/
/*                 CLK Sources                */
/**********************************************/
#define MRCC_HSI_CLK_SOURCE					0
#define MRCC_HSE_CRYSTAL_CLK_SOURCE			1
#define MRCC_HSE_USER_CLK_SOURCE			2
#define MRCC_PLL_HSI_CLK_SOURCE				3
#define MRCC_PLL_HSE_CRYSTAL_CLK_SOURCE		4
#define MRCC_PLL_HSE_USER_CLK_SOURCE		5

/**********************************************/
/*               PLLP Prescalers              */
/**********************************************/
#define MRCC_PLLP_VALUE_2		            0b00
#define MRCC_PLLP_VALUE_4		            0b01
#define MRCC_PLLP_VALUE_6		            0b10
#define MRCC_PLLP_VALUE_8		            0b11

/**********************************************/
/*               AHB Prescalers               */
/**********************************************/
#define MRCC_AHB_PRESCALE_BY_001		    0b0000
#define MRCC_AHB_PRESCALE_BY_002		    0b1000
#define MRCC_AHB_PRESCALE_BY_004		    0b1001
#define MRCC_AHB_PRESCALE_BY_008		    0b1010
#define MRCC_AHB_PRESCALE_BY_016		    0b1011
#define MRCC_AHB_PRESCALE_BY_064		    0b1100
#define MRCC_AHB_PRESCALE_BY_128		    0b1101
#define MRCC_AHB_PRESCALE_BY_256		    0b1110
#define MRCC_AHB_PRESCALE_BY_512		    0b1111

/**********************************************/
/*               APB Prescalers               */
/**********************************************/
#define MRCC_APB_PRESCALE_BY_01			    0b000
#define MRCC_APB_PRESCALE_BY_02			    0b100
#define MRCC_APB_PRESCALE_BY_04			    0b101
#define MRCC_APB_PRESCALE_BY_08			    0b110
#define MRCC_APB_PRESCALE_BY_16			    0b111

/**********************************************/
/*           SW CLK Source Selector           */
/**********************************************/
#define MRCC_SW_SWITCH_TO_HSI			    0b00
#define MRCC_SW_SWITCH_TO_HSE			    0b01
#define MRCC_SW_SWITCH_TO_PLL			    0b10

/**********************************************/
/*              CR BITS Mapping               */
/**********************************************/
#define MRCC_CR_HSION_BIT				    0
#define MRCC_CR_HSIRDY_BIT				    1
#define MRCC_CR_HSITRIM_BIT				    3
#define MRCC_CR_HSEON_BIT				    16
#define MRCC_CR_HSERDY_BIT				    17
#define MRCC_CR_HSEBYP_BIT				    18
#define MRCC_CR_PLLON_BIT				    24
#define MRCC_CR_PLLRDY_BIT				    25

/**********************************************/
/*            PLLCFGR BITS Mapping            */
/**********************************************/
#define MRCC_PLLCFGR_PLLM_BIT			    0
#define MRCC_PLLCFGR_PLLN_BIT			    6
#define MRCC_PLLCFGR_PLLP_BIT			    16
#define MRCC_PLLCFGR_PLLSRC_BIT			    22

/**********************************************/
/*             CFGR BITS Mapping              */
/**********************************************/
#define MRCC_CFGR_SW_BIT				    0
#define MRCC_CFGR_HPRE_BIT				    4
#define MRCC_CFGR_PPRE1_BIT				    10
#define MRCC_CFGR_PPRE2_BIT				    13


#endif /* _MRCC_PRIVATE_H_ */
