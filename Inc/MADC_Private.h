/******************************************************/
/* SWC: ADC Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of ADC            */
/******************************************************/
/* Header File Guard */
#ifndef _MADC_PRIVATE_H_
#define _MADC_PRIVATE_H_

/**********************************************/
/*           ADC Register Structure           */
/**********************************************/
typedef struct {
	volatile u32 SR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMPR[2];
	volatile u32 JOFR[4];
	volatile u32 HTR;
	volatile u32 LTR;
	volatile u32 SQR[3];
	volatile u32 JSQR;
	volatile u32 JDR[4];
	volatile u32 DR;
} ADC_t;

/**********************************************/
/*           ADC Structure Pointer            */
/**********************************************/
/* ADC1 Base Address: 0x4001 2000 */
#define MADC1_BASE_ADDRESS			0x40012000
#define ADC1						((ADC_t*)MADC1_BASE_ADDRESS)
#define ADC1_CCR					*((volatile u32*)0x40015004)

/**********************************************/
/*            Clock Prescale Values           */
/**********************************************/
#define MADC_CLK_DIV_BY_2			0b00
#define MADC_CLK_DIV_BY_4			0b01
#define MADC_CLK_DIV_BY_6			0b10
#define MADC_CLK_DIV_BY_8			0b11

/**********************************************/
/*               SR BITS Mapping              */
/**********************************************/
#define MADC_SR_AWD_BIT						0
#define MADC_SR_EOC_BIT						1
#define MADC_SR_JEOC_BIT					2
#define MADC_SR_JSTRT_BIT					3
#define MADC_SR_STRT_BIT					4
#define MADC_SR_OVR_BIT						5

/**********************************************/
/*              CR1 BITS Mapping              */
/**********************************************/
#define MADC_CR1_AWDCH0_BIT					0
#define MADC_CR1_AWDCH1_BIT					1
#define MADC_CR1_AWDCH2_BIT					2
#define MADC_CR1_AWDCH3_BIT					3
#define MADC_CR1_AWDCH4_BIT					4
#define MADC_CR1_EOCIE_BIT					5
#define MADC_CR1_AWDIE_BIT					6
#define MADC_CR1_JEOCIE_BIT					7
#define MADC_CR1_SCAN_BIT					8
#define MADC_CR1_AWDSGL_BIT					9
#define MADC_CR1_JAUTO_BIT					10
#define MADC_CR1_DISCEN_BIT					11
#define MADC_CR1_JDISCEN_BIT				12
#define MADC_CR1_DISCNUM0_BIT				13
#define MADC_CR1_DISCNUM1_BIT				14
#define MADC_CR1_DISCNUM2_BIT				15
#define MADC_CR1_JAWDEN_BIT					22
#define MADC_CR1_AWDEN_BIT					23
#define MADC_CR1_RES0_BIT					24
#define MADC_CR1_RES1_BIT					25
#define MADC_CR1_OVRIE_BIT					26

/**********************************************/
/*              CR2 BITS Mapping              */
/**********************************************/
#define MADC_CR2_ADON_BIT					0
#define MADC_CR2_CONT_BIT					1
#define MADC_CR2_DMA_BIT					8
#define MADC_CR2_DDS_BIT					9
#define MADC_CR2_EOCS_BIT					10
#define MADC_CR2_ALLIGN_BIT					11
#define MADC_CR2_JEXTSEL0_BIT				16
#define MADC_CR2_JEXTSEL1_BIT				17
#define MADC_CR2_JEXTSEL2_BIT				18
#define MADC_CR2_JEXTSEL3_BIT				19
#define MADC_CR2_JEXTEN0_BIT				20
#define MADC_CR2_JEXTEN1_BIT				21
#define MADC_CR2_JSWSTART_BIT				22
#define MADC_CR2_EXTSEL0_BIT				24
#define MADC_CR2_EXTSEL1_BIT				25
#define MADC_CR2_EXTSEL2_BIT				26
#define MADC_CR2_EXTSEL3_BIT				27
#define MADC_CR2_EXTEN0_BIT					28
#define MADC_CR2_EXTEN1_BIT					29
#define MADC_CR2_SWSTART_BIT				30

/**********************************************/
/*              CCR BITS Mapping              */
/**********************************************/
#define MADC_CCR_ADCPRE0_BIT				16
#define MADC_CCR_ADCPRE1_BIT				17
#define MADC_CCR_VBATE_BIT					22
#define MADC_CCR_TSVREFE_BIT				23

#endif /* _MADC_PRIVATE_H_ */
