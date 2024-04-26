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
#define ADC_CCR						*((volatile u32*)0x40015004)


/**********************************************/
/*        Single or Multichannel Modes        */
/**********************************************/
#define MADC_SINGLE_CONVERSION_MODE		0b0
#define MADC_SCAN_CONVERSION_MODE		0b1

/**********************************************/
/*            ADC Conversion Modes            */
/**********************************************/
#define MADC_NORMAL_CONVERSION			0b00
#define MADC_CONTINUOUS_CONVERSION		0b01
#define MADC_DISCONTINUOUS_CONVERSION	0b10

/**********************************************/
/*         End Of Conversion Location         */
/**********************************************/
#define MADC_EOC_REGULAR_SEQUENCE_END       0b0
#define MADC_EOC_REGULAR_CONVERSION_END     0b1

/**********************************************/
/*            Clock Prescale Values           */
/**********************************************/
#define MADC_CLK_DIV_BY_2			0b00
#define MADC_CLK_DIV_BY_4			0b01
#define MADC_CLK_DIV_BY_6			0b10
#define MADC_CLK_DIV_BY_8			0b11

/**********************************************/
/*            Data Allignment Modes           */
/**********************************************/
#define MADC_ALLIGN_RIGHT		          0
#define MADC_ALLIGN_LEFT       			  1

/**********************************************/
/*              Resolution Sizes              */
/**********************************************/
#define MADC_RESOLUTION_12_BITS             0b00
#define MADC_RESOLUTION_10_BITS             0b01
#define MADC_RESOLUTION_08_BITS             0b10
#define MADC_RESOLUTION_06_BITS             0b11

/**********************************************/
/*         External Trigger Detection         */
/**********************************************/
#define MADC_TRIG_EDGE_DISABLED     		0b00
#define MADC_TRIG_EDGE_RISING       		0b01
#define MADC_TRIG_EDGE_FALLING      		0b10
#define MADC_TRIG_EDGE_BOTH         		0b11

/**********************************************/
/*     Regular External Trigger Detection     */
/**********************************************/
#define MADC_EVENT_TRIG_REGULAR_TIM1CC1     0b0000
#define MADC_EVENT_TRIG_REGULAR_TIM1CC2     0b0001
#define MADC_EVENT_TRIG_REGULAR_TIM1CC3     0b0010
#define MADC_EVENT_TRIG_REGULAR_TIM2CC2     0b0011
#define MADC_EVENT_TRIG_REGULAR_TIM2CC3     0b0100
#define MADC_EVENT_TRIG_REGULAR_TIM2CC4     0b0101
#define MADC_EVENT_TRIG_REGULAR_TIM2TRGO    0b0110
#define MADC_EVENT_TRIG_REGULAR_TIM3CC1     0b0111
#define MADC_EVENT_TRIG_REGULAR_TIM3TRGO    0b1000
#define MADC_EVENT_TRIG_REGULAR_TIM4CC4     0b1001
#define MADC_EVENT_TRIG_REGULAR_TIM5CC1     0b1010
#define MADC_EVENT_TRIG_REGULAR_TIM5CC2     0b1011
#define MADC_EVENT_TRIG_REGULAR_TIM5CC3     0b1100
#define MADC_EVENT_TRIG_REGULAR_EXTI11      0b1111

/**********************************************/
/*     Injected External Trigger Detection    */
/**********************************************/
#define MADC_EVENT_TRIG_INJECTED_TIM1CC4    0b0000
#define MADC_EVENT_TRIG_INJECTED_TIM1TRGO   0b0001
#define MADC_EVENT_TRIG_INJECTED_TIM2CC1    0b0010
#define MADC_EVENT_TRIG_INJECTED_TIM2TRGO   0b0011
#define MADC_EVENT_TRIG_INJECTED_TIM3CC2    0b0100
#define MADC_EVENT_TRIG_INJECTED_TIM3CC4    0b0101
#define MADC_EVENT_TRIG_INJECTED_TIM4CC1    0b0110
#define MADC_EVENT_TRIG_INJECTED_TIM4CC2    0b0111
#define MADC_EVENT_TRIG_INJECTED_TIM4CC3    0b1000
#define MADC_EVENT_TRIG_INJECTED_TIM4TRGO   0b1001
#define MADC_EVENT_TRIG_INJECTED_TIM5CC4    0b1010
#define MADC_EVENT_TRIG_INJECTED_TIM5TRGO   0b1011
#define MADC_EVENT_TRIG_INJECTED_EXTI15     0b1111



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
/*              SQR1 BITS Mapping             */
/**********************************************/
#define MADC_SQR1_L0_BIT					20

/**********************************************/
/*              JSQR BITS Mapping             */
/**********************************************/
#define MADC_JSQR_JL0_BIT					20

/**********************************************/
/*              CCR BITS Mapping              */
/**********************************************/
#define MADC_CCR_ADCPRE0_BIT				16
#define MADC_CCR_ADCPRE1_BIT				17
#define MADC_CCR_VBATE_BIT					22
#define MADC_CCR_TSVREFE_BIT				23

#endif /* _MADC_PRIVATE_H_ */
