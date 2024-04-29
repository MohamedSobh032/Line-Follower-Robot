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
	u8 SingleOrMultiple;
	MADC_CHANNEL Channel;
	u16 HighThreshold;
	u16 LowThreshold;
} MADC_AWDTypeDef;


void MADC_vInit(void);
void MADC_vAWDInit(MADC_AWDTypeDef* A_InitStruct);
void MADC_vEnable(u8 Copy_u8EnableReg, u8 Copy_u8EnableInj);

volatile u32* MADC_u32SetRegularDMA(u8 Copy_u8Status);

void MADC_vSetSamplingTime(MADC_CHANNEL Channel, u8 Copy_u8SampleTime);
void MADC_vSetNumberOfConversions(u8 Copy_u8Group, u8 Copy_u8Conversions);
void MADC_vSetSequence(u8 Copy_u8Group, u8 Copy_u8SeqNumber, u8 Copy_u8Channel);

void MADC_vSetInterrupt(u8 Copy_u8Group, u8 Copy_u8EnableValue);


u16 MADC_u16ReadSingleConversion(void);

/**********************************************/
/*             ADC ENABLE DISABLE             */
/**********************************************/
#define MADC_DISABLE             		  		0
#define MADC_ENABLE                				1

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
/*         Conversion Sampling Cycles         */
/**********************************************/
#define MADC_SAMPLING_CYCLES_3				0b000
#define MADC_SAMPLING_CYCLES_15				0b001
#define MADC_SAMPLING_CYCLES_28				0b010
#define MADC_SAMPLING_CYCLES_56				0b011
#define MADC_SAMPLING_CYCLES_84				0b100
#define MADC_SAMPLING_CYCLES_112			0b101
#define MADC_SAMPLING_CYCLES_144			0b110
#define MADC_SAMPLING_CYCLES_480			0b111

/**********************************************/
/*           ADC Conversion Lengths           */
/**********************************************/
#define MADC_ONE_CONVERSION					0b0000
#define MADC_TWO_CONVERSIONS				0b0001
#define MADC_THREE_CONVERSIONS				0b0010
#define MADC_FOUR_CONVERSIONS				0b0011
#define MADC_FIVE_CONVERSIONS				0b0100
#define MADC_SIX_CONVERSIONS				0b0101
#define MADC_SEVEN_CONVERSIONS				0b0110
#define MADC_EIGHT_CONVERSIONS				0b0111
#define MADC_NINE_CONVERSIONS				0b1000

/**********************************************/
/*              Sequence Location             */
/**********************************************/
#define MADC_SEQUENCE_1						0
#define MADC_SEQUENCE_2						1
#define MADC_SEQUENCE_3						2
#define MADC_SEQUENCE_4						3
#define MADC_SEQUENCE_5						4
#define MADC_SEQUENCE_6						5
#define MADC_SEQUENCE_7						6
#define MADC_SEQUENCE_8						7
#define MADC_SEQUENCE_9						8
#define MADC_SEQUENCE_10					9
#define MADC_SEQUENCE_11					10
#define MADC_SEQUENCE_12					11
#define MADC_SEQUENCE_13					12


#endif /* _MADC_INTERFACE_H_ */
