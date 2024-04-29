/******************************************************/
/* SWC: GPT Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of GPT            */
/******************************************************/
/* Header File Guard */
#ifndef _MGPT_INTERFACE_H_
#define _MGPT_INTERFACE_H_

/**********************************************/
/*       GPT 2 --> 5 Register Structure       */
/**********************************************/
typedef struct {
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR[2];
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 RES0;
	volatile u32 CCR[4];
	volatile u32 RES1;
	volatile u32 DCR;
	volatile u32 DMAR;
	volatile u32 OR;   /* ONLY FOR TIM2 AND TIM5 */
} GPT_t;

/**********************************************/
/*       GPT 2 --> 5 Structure Pointers       */
/**********************************************/
/* TIM2 Base Address: 0x4000 0000 */
#define MGPT2_BASE_ADDRESS			0x40000000
#define GPT2						((GPT_t*)MGPT2_BASE_ADDRESS)
/* TIM3 Base Address: 0x4000 0400 */
#define MGPT3_BASE_ADDRESS			0x40000400
#define GPT3						((GPT_t*)MGPT3_BASE_ADDRESS)
/* TIM4 Base Address: 0x4000 0800 */
#define MGPT4_BASE_ADDRESS			0x40000800
#define GPT4						((GPT_t*)MGPT4_BASE_ADDRESS)
/* TIM5 Base Address: 0x4000 0C00 */
#define MGPT5_BASE_ADDRESS			0x40000C00
#define GPT5						((GPT_t*)MGPT5_BASE_ADDRESS)

/**********************************************/
/*     TIMER PWM INITIALIZATION STRUCTURE     */
/**********************************************/
typedef struct {
	u8 Channel;
	u8 PWMMode;
	u32 Period;
	u16 Prescaler;
	u8 CountingMode;
	u8 Direction;
	u8 Polarity;
} MGPT_PWMInitTypeDef;



/**********************************************/
/*           TIME COUNTER FUNCTIONS           */
/**********************************************/
void MGPT_vTimeCounterInit(GPT_t* GPTx, u8 Copy_u8TickTime, void (*ptr)(void));
/**********************************************/
/*                PWM FUNCTIONS               */
/**********************************************/
void MGPT_vPWMInit(GPT_t* GPTx, MGPT_PWMInitTypeDef* A_InitStruct);
void MGPT_vSetPWMDutyCycle(GPT_t* GPTx, u8 Copy_u8Channel, u32 Copy_u32DutyCycle);




/**********************************************/
/*                 GPT STATUS                 */
/**********************************************/
#define MGPT_DISABLE				0
#define MGPT_ENABLE					1

/**********************************************/
/*               TIMER CHANNELS               */
/**********************************************/
#define MGPT_CHANNEL_1				0
#define MGPT_CHANNEL_2				1
#define MGPT_CHANNEL_3				2
#define MGPT_CHANNEL_4				3

/**********************************************/
/*               TIMER PWM MODES              */
/**********************************************/
#define MGPT_PWM_MODE_1				0b110
#define MGPT_PWM_MODE_2				0b111

/**********************************************/
/*       TIMER CHANNELS OUTPUT POLARITY       */
/**********************************************/
#define MGPT_CHANNEL_OUTPUT_ACTIVE_HIGH		0
#define MGPT_CHANNEL_OUTPUT_ACTIVE_LOW		1

/**********************************************/
/*       COUNTING MODES AND ALLIGNMENTS       */
/**********************************************/
#define MGPT_ALLIGNMENT_EDGE_MODE			0b00
#define MGPT_ALLGINMENT_CENTER_DOWN			0b01
#define MGPT_ALLIGNMENT_CENTER_UP			0b10
#define MGPT_ALLIGNMENT_CENTER_UP_DOWN		0b11

/**********************************************/
/*               DIRECTION MODES              */
/**********************************************/
#define MGPT_DIRECTION_UP_COUNTER			0b0
#define MGPT_DIRECITON_DOWN_COUNTER			0b1

/**********************************************/
/*                 TICK TIMES                 */
/**********************************************/
#define MGPT_TICK_TIME_MICRO_SECOND			0b00
#define MGPT_TICK_TIME_100_MICRO_SECONDS	0b01
#define MGPT_TICK_TIME_MILLI_SECOND			0b10
#define MGPT_TICK_TIME_10_MILLI_SECONDS		0b11



#endif /* _MGPT_INTERFACE_H_ */
