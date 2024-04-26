/******************************************************/
/* SWC: ADC Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of ADC            */
/******************************************************/
/* Header File Guard */
#ifndef _MADC_INTERFACE_H_
#define _MADC_INTERFACE_H_

/**********************************************/
/*                ADC Channels                */
/**********************************************/
typedef enum {
	MADC_CHANNEL0  = 0b00000,
	MADC_CHANNEL1  = 0b00001,
	MADC_CHANNEL2  = 0b00010,
	MADC_CHANNEL3  = 0b00011,
	MADC_CHANNEL4  = 0b00100,
	MADC_CHANNEL5  = 0b00101,
	MADC_CHANNEL6  = 0b00110,
	MADC_CHANNEL7  = 0b00111,
	MADC_CHANNEL8  = 0b01000,
	MADC_CHANNEL9  = 0b01001
} MADC_CHANNEL;

/**********************************************/
/*        ADC Initialization Structures       */
/**********************************************/
typedef struct {
	u8 RegularEnable;
	u8 InjectedEnable;
	u8 SingleOrMultiple;
	MADC_CHANNEL Channel;
	u16 HighThreshold;
	u16 LowThreshold;
} MADC_AWDTypeDef;



void MADC_vGeneralInit(u8 Copy_u8DataAllignment, u8 Copy_u8Resolution);
void MADC_vAWDInit(MADC_AWDTypeDef* A_InitStruct);

void MADC_vEnableScanMode(void);

void MADC_vEnableDiscontinuousMode(u8 Copy_u8Group, u8 Copy_u8DiscontinousNumber);
void MADC_vEnableContinuousMode(void);

void MADC_vEnableAutomaticInjection(void);

void MADC_vSetExternalTrigger(u8 Copy_u8Group, u8 Copy_u8TriggeringEdge, u8 Copy_u8TriggerSource);

void MADC_vEnableInjectedInterrupt(void);
void MADC_vEnableRegularInterrupt(void);

void MADC_vSetSamplingTime(u8 Copy_u8Channel, u8 Copy_u8SampleTime);

void MADC_vSetNumberOfConversions(u8 Copy_u8Conversions);

void MADC_vSetSequence(u8 Copy_u8Group, u8 Copy_u8SeqNumber, u8 Copy_u8Channel);

/**********************************************/
/*             ADC ENABLE DISABLE             */
/**********************************************/
#define MADC_DISABLE             		  		0
#define MADC_ENABLE                				1

/**********************************************/
/*            Data Allignment Modes           */
/**********************************************/
#define MADC_DATA_ALLIGN_RIGHT		          0
#define MADC_DATA_ALLIGN_LEFT       		  1

/**********************************************/
/*              Resolution Sizes              */
/**********************************************/
#define MADC_RESOLUTION_12_BITS             0b00
#define MADC_RESOLUTION_10_BITS             0b01
#define MADC_RESOLUTION_08_BITS             0b10
#define MADC_RESOLUTION_06_BITS             0b11

/**********************************************/
/*    Analog Watchdog Single Multiple Scan    */
/**********************************************/
#define MADC_AWD_MULTIPLE_CHANNEL_SCAN		0
#define MADC_AWD_SINGLE_CHANNEL_SCAN		1

/**********************************************/
/*        Regular or Injected Grouping        */
/**********************************************/
#define MADC_REGULAR_GROUP					0
#define MADC_INJECTED_GROUP					1

/**********************************************/
/*           Discontinuous Counters           */
/**********************************************/
#define MADC_DISCONT_1_CHANNEL              0b000
#define MADC_DISCONT_2_CHANNELS             0b001
#define MADC_DISCONT_3_CHANNELS             0b010
#define MADC_DISCONT_4_CHANNELS             0b011
#define MADC_DISCONT_5_CHANNELS             0b100
#define MADC_DISCONT_6_CHANNELS             0b101
#define MADC_DISCONT_7_CHANNELS             0b110
#define MADC_DISCONT_8_CHANNELS             0b111

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
/*      End Of Conversion Selection Modes     */
/**********************************************/
#define MADC_EOC_REGULAR_SEQUENCE_END       0
#define MADC_EOC_REGULAR_CONVERSION_END     1

/**********************************************/
/*          Conversion Sequence Modes         */
/**********************************************/
#define MADC_SINGLE_CONVERSION              0
#define MADC_CONTINUOUS_CONVERSION          1

#endif /* _MADC_INTERFACE_H_ */
