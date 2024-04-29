#ifndef _MAIN_H_
#define _MAIN_H_



/********************************** APPLICATION CODE SETTING **********************************/
/* DEFINE RECEIVED STRING FROM MOBILE APPLICATION LENGTH */
#define APP_MOBILE_MESSAGE_LENGTH			6U
/**********************************************************************************************/



/************************************** HARDWARE SETTING **************************************/
/* DEFINE IR ARRAY PINS */
#define APP_IR0			GPIOA, MGPIO_PIN00
#define APP_IR1			GPIOA, MGPIO_PIN01
#define APP_IR2			GPIOA, MGPIO_PIN02
#define APP_IR3			GPIOA, MGPIO_PIN03
#define APP_IR4			GPIOA, MGPIO_PIN04
#define APP_IR5			GPIOA, MGPIO_PIN05
	/* DEFINE THE CHANNELS */
#define APP_IR0_CHANNEL	MADC_CHANNEL0
#define APP_IR1_CHANNEL	MADC_CHANNEL1
#define APP_IR2_CHANNEL	MADC_CHANNEL2
#define APP_IR3_CHANNEL	MADC_CHANNEL3
#define APP_IR4_CHANNEL	MADC_CHANNEL4
#define APP_IR5_CHANNEL	MADC_CHANNEL5

/* DEFINE USART FOR MOBILE APPLICATION */
#define APP_MOBILE_USART		USART1
	/* DEFINE THE PINS */
#define APP_MOBILE_USART_TX		GPIOA, MGPIO_PIN09
#define APP_MOBILE_USART_RX		GPIOA, MGPIO_PIN10
	/* DEFINE THE DIRECTION */
#define APP_MOBILE_USART_AF		MGPIO_AF07

/* PWM TIMER GENERATOR */
#define APP_TIM_PWM				GPT3
#define APP_CHANNEL_PWM			MGPT_CHANNEL_1
#define APP_PWM_PERIOD			10000
#define APP_PWM_PRESCALER		1
	/* DEFINE THE PINS */
#define APP_TIM_PWM_PIN			GPIOB, MGPIO_PIN04
#define APP_TIM_PWM_AF			MGPIO_AF02

/* TIME COUNTER TIMER */
#define APP_TIM_COUNTER				GPT2
#define APP_TIM_COUNTER_TICK_TIME	MGPT_TICK_TIME_MICRO_SECOND
#define APP_TIM_COUNTER_INT_ID		28
/**********************************************************************************************/

#endif /* _MAIN_H_ */
