/******************************************************/
/* SWC: GPT Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of GPT            */
/******************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"

#include "MGPT_Private.h"
#include "MGPT_Config.h"
#include "MGPT_Interface.h"


void (*MGPT_CALLBACKS[4])(void) = {(void*)0};

/*****************************************************************/
/* Func. Name: MGPT_vTimeCounterInit                             */
/* i/p arguments: GPTx: TIM2 --> TIM5 ONLY                       */
/* i/p arguments: A_InitStruct: Initialization Structure         */
/* o/p arguments: nothing                                        */
/* Desc. : This API Initializes the Selected Timer to Count Time */
/*****************************************************************/
void MGPT_vTimeCounterInit(GPT_t* GPTx, u8 Copy_u8TickTime, void (*ptr)(void)) {
	/* SET THE PRESCALER TO THE WANTED VALUE */
	switch (Copy_u8TickTime) {
		case MGPT_TICK_TIME_MICRO_SECOND:      GPTx->PSC = (__MGPT_PCLK__ / 1000000) - 1; break;
		case MGPT_TICK_TIME_100_MICRO_SECONDS: GPTx->PSC = (__MGPT_PCLK__ / 10000)   - 1; break;
		case MGPT_TICK_TIME_MILLI_SECOND:      GPTx->PSC = (__MGPT_PCLK__ / 1000)    - 1; break;
		case MGPT_TICK_TIME_10_MILLI_SECONDS:  GPTx->PSC = (__MGPT_PCLK__ / 100)     - 1; break;
		default: 							   GPTx->PSC = (__MGPT_PCLK__ / 1000000) - 1; break;
	}

	/* SET THE TIMER AS AN UPCOUNTER */
	CLR_BIT(GPTx->CR1, MGPT_CR1_DIR_BIT);

	/* SET THE ARR REGISTER TO MAXIMUM VALUE */
	GPTx->ARR = 1000000;

	/* SET THE CALL BACK FUNCTION */
	if (GPTx == GPT2)      { MGPT_CALLBACKS[0] = ptr; }
	else if (GPTx == GPT3) { MGPT_CALLBACKS[1] = ptr; }
	else if (GPTx == GPT4) { MGPT_CALLBACKS[2] = ptr; }
	else if (GPTx == GPT5) { MGPT_CALLBACKS[3] = ptr; }

	/* ENABLE INTERRUPT */
	SET_BIT(GPTx->DIER, MGPT_DIER_UIE_BIT);

	/* START COUNTING */
	SET_BIT(GPTx->CR1, MGPT_CR1_CEN_BIT);
}

/***************************************************************/
/* Func. Name: MGPT_vPWMInit                                   */
/* i/p arguments: GPTx: TIM2 --> TIM5 ONLY                     */
/* i/p arguments: A_InitStruct: Initialization Structure       */
/* o/p arguments: nothing                                      */
/* Desc. : This API Initializes the Selected Timer to PWM Mode */
/***************************************************************/
void MGPT_vPWMInit(GPT_t* GPTx, MGPT_PWMInitTypeDef* A_InitStruct) {
	/* CLEAR CCxS[1:0] BITS
	 * SET THE POLARITY OF THE OUTPUT
	 * SET THE PWM MODE
	 * SET THE PRESCALER
	 * ENABLE PRELOAD */
	switch (A_InitStruct->Channel) {
		case MGPT_CHANNEL_1: WRITE_BITS(GPTx->CCMR[0], 0b00, TWO_BITS, MGPT_CCMR1_CC1S_BIT);
							 if (A_InitStruct->Polarity) { SET_BIT(GPTx->CCER, MGPT_CCER_CC1P_BIT); }
							 else 	 					 { CLR_BIT(GPTx->CCER, MGPT_CCER_CC1P_BIT); }
							 WRITE_BITS(GPTx->CCMR[0], A_InitStruct->PWMMode, THREE_BITS, MGPT_CCMR1_OC1M0_BIT);
							 GPTx->PSC = (u32)A_InitStruct->Prescaler - 1;
							 GPTx->ARR = A_InitStruct->Period;
							 SET_BIT(GPTx->CCMR[0], MGPT_CCMR1_OC1PE_BIT);
							 break;

		case MGPT_CHANNEL_2: WRITE_BITS(GPTx->CCMR[0], 0b00, TWO_BITS, MGPT_CCMR1_CC2S_BIT);
							 if (A_InitStruct->Polarity) { SET_BIT(GPTx->CCER, MGPT_CCER_CC2P_BIT); }
							 else 	 					 { CLR_BIT(GPTx->CCER, MGPT_CCER_CC2P_BIT); }
							 WRITE_BITS(GPTx->CCMR[0], A_InitStruct->PWMMode, THREE_BITS, MGPT_CCMR1_OC2M0_BIT);
							 GPTx->PSC = (u32)A_InitStruct->Prescaler;
							 GPTx->ARR = A_InitStruct->Period;
							 SET_BIT(GPTx->CCMR[0], MGPT_CCMR1_OC2PE_BIT);
							 break;

		case MGPT_CHANNEL_3: WRITE_BITS(GPTx->CCMR[1], 0b00, TWO_BITS, MGPT_CCMR2_CC3S_BIT);
							 if (A_InitStruct->Polarity) { SET_BIT(GPTx->CCER, MGPT_CCER_CC3P_BIT); }
							 else 	 					 { CLR_BIT(GPTx->CCER, MGPT_CCER_CC3P_BIT); }
							 WRITE_BITS(GPTx->CCMR[1], A_InitStruct->PWMMode, THREE_BITS, MGPT_CCMR2_OC3M0_BIT);
							 GPTx->PSC = (u32)A_InitStruct->Prescaler;
							 GPTx->ARR = A_InitStruct->Period;
							 SET_BIT(GPTx->CCMR[1], MGPT_CCMR2_OC3PE_BIT);
							 break;

		case MGPT_CHANNEL_4: WRITE_BITS(GPTx->CCMR[1], 0b00, TWO_BITS, MGPT_CCMR2_CC4S_BIT);
							 if (A_InitStruct->Polarity) { SET_BIT(GPTx->CCER, MGPT_CCER_CC4P_BIT); }
							 else 	 					 { CLR_BIT(GPTx->CCER, MGPT_CCER_CC4P_BIT); }
							 WRITE_BITS(GPTx->CCMR[1], A_InitStruct->PWMMode, THREE_BITS, MGPT_CCMR2_OC4M0_BIT);
							 GPTx->PSC = (u32)A_InitStruct->Prescaler;
							 GPTx->ARR = A_InitStruct->Period;
							 SET_BIT(GPTx->CCMR[1], MGPT_CCMR2_OC4PE_BIT);
							 break;
		default: break;
	}
	/* ENABLE AUTO-RELOAD PRELOAD */
	SET_BIT(GPTx->CR1, MGPT_CR1_ARPE_BIT);
	/* SET COUNTING MODE AND DIRECTION */
	WRITE_BITS(GPTx->CR1, A_InitStruct->CountingMode, TWO_BITS, MGPT_CR1_CMS0_BIT);
	if (!A_InitStruct->CountingMode) {
		if (A_InitStruct->Direction) { SET_BIT(GPTx->CR1, MGPT_CR1_DIR_BIT); }
		else						 { CLR_BIT(GPTx->CR1, MGPT_CR1_DIR_BIT); }
	}
	/* ENABLE CAPTURE/COMPARE OUTPUT */
	switch (A_InitStruct->Channel) {
		case MGPT_CHANNEL_1: SET_BIT(GPTx->CCER, MGPT_CCER_CC1E_BIT); break;
		case MGPT_CHANNEL_2: SET_BIT(GPTx->CCER, MGPT_CCER_CC2E_BIT); break;
		case MGPT_CHANNEL_3: SET_BIT(GPTx->CCER, MGPT_CCER_CC3E_BIT); break;
		case MGPT_CHANNEL_4: SET_BIT(GPTx->CCER, MGPT_CCER_CC4E_BIT); break;
		default: break;
	}
	/* ENABLE COUNTER */
	SET_BIT(GPTx->CR1, MGPT_CR1_CEN_BIT);
}

/**************************************************************************/
/* Func. Name: MGPT_vSetPWMDutyCycle                                      */
/* i/p arguments: GPTx: TIM2 --> TIM5 ONLY                                */
/* i/p arguments: Copy_u8Channel: MGPT_CHANNEL_<Number>					  */
/* i/p arguments: Copy_u32DutyCycle: Duty Cycle                           */
/* o/p arguments: nothing                                                 */
/* Desc. : This API Sets the Duty Cycle of the Selected Timer in PWM Mode */
/**************************************************************************/
void MGPT_vSetPWMDutyCycle(GPT_t* GPTx, u8 Copy_u8Channel, u32 Copy_u32DutyCycle) {
	GPTx->CCR[Copy_u8Channel] = Copy_u32DutyCycle;
}



/**********************************************/
/*             INTERRUPT HANDLERS             */
/**********************************************/
void TIM2_IRQHandler(void) {
	GPT2->SR = 0;
	GPT2->CNT = 0;
	MGPT_CALLBACKS[0]();
}

void TIM3_IRQHandler(void) {
	GPT3->SR = 0;
	MGPT_CALLBACKS[1]();
}

void TIM4_IRQHandler(void) {
	GPT4->SR = 0;
	MGPT_CALLBACKS[2]();
}

void TIM5_IRQHandler(void) {
	GPT5->SR = 0;
	MGPT_CALLBACKS[3]();
}
