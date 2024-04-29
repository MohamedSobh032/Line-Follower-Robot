/******************************************************/
/* SWC: GPT Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of GPT            */
/******************************************************/
/* Header File Guard */
#ifndef _MGPT_PRIVATE_H_
#define _MGPT_PRIVATE_H_

/**********************************************/
/*              CR1 BITS Mapping              */
/**********************************************/
#define MGPT_CR1_CEN_BIT				0
#define MGPT_CR1_DIR_BIT				4
#define MGPT_CR1_CMS0_BIT				5
#define MGPT_CR1_CMS1_BIT				6
#define MGPT_CR1_ARPE_BIT				7

/**********************************************/
/*              DIER BITS Mapping             */
/**********************************************/
#define MGPT_DIER_UIE_BIT				0

/**********************************************/
/*             CCMR1 BITS Mapping             */
/**********************************************/
#define MGPT_CCMR1_CC1S_BIT				0
#define MGPT_CCMR1_OC1PE_BIT			3
#define MGPT_CCMR1_OC1M0_BIT			4
#define MGPT_CCMR1_OC1M1_BIT			5
#define MGPT_CCMR1_OC1M2_BIT			6
#define MGPT_CCMR1_CC2S_BIT				8
#define MGPT_CCMR1_OC2PE_BIT			11
#define MGPT_CCMR1_OC2M0_BIT			12
#define MGPT_CCMR1_OC2M1_BIT			13
#define MGPT_CCMR1_OC2M2_BIT			14

/**********************************************/
/*             CCMR2 BITS Mapping             */
/**********************************************/
#define MGPT_CCMR2_CC3S_BIT				0
#define MGPT_CCMR2_OC3PE_BIT			3
#define MGPT_CCMR2_OC3M0_BIT			4
#define MGPT_CCMR2_OC3M1_BIT			5
#define MGPT_CCMR2_OC3M2_BIT			6
#define MGPT_CCMR2_CC4S_BIT				8
#define MGPT_CCMR2_OC4PE_BIT			11
#define MGPT_CCMR2_OC4M0_BIT			12
#define MGPT_CCMR2_OC4M1_BIT			13
#define MGPT_CCMR2_OC4M2_BIT			14

/**********************************************/
/*              CCER BITS Mapping             */
/**********************************************/
#define MGPT_CCER_CC1E_BIT				0
#define MGPT_CCER_CC1P_BIT				1
#define MGPT_CCER_CC2E_BIT				4
#define MGPT_CCER_CC2P_BIT				5
#define MGPT_CCER_CC3E_BIT				8
#define MGPT_CCER_CC3P_BIT				9
#define MGPT_CCER_CC4E_BIT				12
#define MGPT_CCER_CC4P_BIT				13



#endif /* _MGPT_PRIVATE_H_ */
