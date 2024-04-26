/******************************************************/
/* SWC: ADC Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of ADC            */
/******************************************************/
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MADC_Private.h"
#include "MADC_Config.h"
#include "MADC_Interface.h"

/**************************************************************************/
/* Func. Name: MADC_vGeneralInit                                          */
/* i/p arguments: Copy_u8DataAllignment: MADC_DATA_ALLIGN_<Allignment>    */
/* i/p arguments: Copy_u8Resolution: MADC_RESOLUTION_<ResolutionNum>_BITS */
/* o/p arguments: nothing                                                 */
/* Desc. : This API Initializes General ADC Settings                      */
/**************************************************************************/
void MADC_vGeneralInit(u8 Copy_u8DataAllignment, u8 Copy_u8Resolution) {
	/* Set the Prescaler of the ADC CLK */
	WRITE_BITS(ADC1_CCR, MADC_CLOCK_PRESCALER, TWO_BITS, MADC_CCR_ADCPRE0_BIT);
	/* Set the Data Allignment */
	WRITE_BITS(ADC1->CR2, Copy_u8DataAllignment, ONE_BIT, MADC_CR2_ALLIGN_BIT);
	/* Set the Resolution of the ADC */
	WRITE_BITS(ADC1->CR1, Copy_u8Resolution, TWO_BITS, MADC_CR1_RES0_BIT);
	/* Set the EOC After Each Regular Conversion */
	SET_BIT(ADC1->CR2, MADC_CR2_EOCS_BIT);
	/* Clear Status Register */
	ADC1->SR = 0;
	/* Wake up the ADC from Power Down Mode */
	SET_BIT(ADC1->CR2, MADC_CR2_ADON_BIT);
}

/**********************************************************/
/* Func. Name: MADC_vAWDInit                              */
/* i/p arguments: A_InitStruct: AWD Initialization Struct */
/* o/p arguments: nothing                                 */
/* Desc. : This API Initializes AWD Settings              */
/**********************************************************/
void MADC_vAWDInit(MADC_AWDTypeDef* A_InitStruct) {
	WRITE_BITS(ADC1->CR1, A_InitStruct->RegularEnable, ONE_BIT, MADC_CR1_AWDEN_BIT);
	WRITE_BITS(ADC1->CR1, A_InitStruct->InjectedEnable, ONE_BIT, MADC_CR1_JAWDEN_BIT);
	WRITE_BITS(ADC1->CR1, A_InitStruct->SingleOrMultiple, ONE_BIT, MADC_CR1_AWDSGL_BIT);
	if (GET_BIT(ADC1->CR1, MADC_CR1_SCAN_BIT)) {
		if (A_InitStruct->SingleOrMultiple == MADC_AWD_SINGLE_CHANNEL_SCAN) {
			WRITE_BITS(ADC1->CR1, A_InitStruct->Channel, FIVE_BITS, MADC_CR1_AWDCH0_BIT);
		}
	}
	WRITE_BITS(ADC1->HTR, A_InitStruct->HighThreshold, TWELVE_BITS, 0);
	WRITE_BITS(ADC1->LTR, A_InitStruct->LowThreshold, TWELVE_BITS, 0);
}

/***************************************************************/
/* Func. Name: MADC_vSetScanMode                               */
/* i/p arguments: Copy_u8EnableValue: MADC_<Enable or Disable> */
/* o/p arguments: nothing                                      */
/* Desc. : This API Enables Scan Mode                          */
/***************************************************************/
void MADC_vSetScanMode(u8 Copy_u8EnableValue) {
	if (Copy_u8EnableValue == MADC_ENABLE) {
		SET_BIT(ADC1->CR1, MADC_CR1_SCAN_BIT);
	} else {
		CLR_BIT(ADC1->CR1, MADC_CR1_SCAN_BIT);
	}
}

/***************************************************************************/
/* Func. Name: MADC_vSetDiscontinuousMode                                  */
/* i/p arguments: Copy_u8EnableValue: MADC_<Enable or Disable>             */
/* i/p arguments: Copy_u8Group: MADC_<Group>_GROUP                         */
/* i/p arguments: Copy_u8DiscontinousNumber: MADC_DISCONT_<Number>_CHANNEL */
/* o/p arguments: nothing                                                  */
/* Desc. : This API Enables Discontinuous Mode for Selected Group          */
/***************************************************************************/
void MADC_vSetDiscontinuousMode(u8 Copy_u8EnableValue, u8 Copy_u8Group, u8 Copy_u8DiscontinousNumber) {
	if (Copy_u8EnableValue == MADC_ENABLE) {
		if (Copy_u8Group == MADC_REGULAR_GROUP) { SET_BIT(ADC1->CR1, MADC_CR1_DISCEN_BIT); }
		else 									{ SET_BIT(ADC1->CR1, MADC_CR1_JDISCEN_BIT); }
		WRITE_BITS(ADC1->CR1, Copy_u8DiscontinousNumber, THREE_BITS, MADC_CR1_DISCNUM0_BIT);
	} else {
		if (Copy_u8Group == MADC_REGULAR_GROUP) { CLR_BIT(ADC1->CR1, MADC_CR1_DISCEN_BIT); }
		else 									{ CLR_BIT(ADC1->CR1, MADC_CR1_JDISCEN_BIT); }
	}
}

/***************************************************************/
/* Func. Name: MADC_vSetContinuousMode                         */
/* i/p arguments: Copy_u8EnableValue: MADC_<Enable or Disable> */
/* o/p arguments: nothing                                      */
/* Desc. : This API Enables continuous Mode for all Groups     */
/***************************************************************/
void MADC_vSetContinuousMode(u8 Copy_u8EnableValue) {
	if (Copy_u8EnableValue == MADC_ENABLE) {
		/* Clear all Discontinuous bits */
		CLR_BIT(ADC1->CR1, MADC_CR1_DISCEN_BIT);
		CLR_BIT(ADC1->CR1, MADC_CR1_JDISCEN_BIT);
		/* Set Continuous bit */
		SET_BIT(ADC1->CR2, MADC_CR2_CONT_BIT);
	} else {
		CLR_BIT(ADC1->CR2, MADC_CR2_CONT_BIT);
	}
}

/***************************************************************/
/* Func. Name: MADC_vSetAutomaticInjection                     */
/* i/p arguments: Copy_u8EnableValue: MADC_<Enable or Disable> */
/* o/p arguments: nothing                                      */
/* Desc. : This API Enables Automatic Injected Conversions     */
/***************************************************************/
void MADC_vSetAutomaticInjection(u8 Copy_u8EnableValue) {
	if (Copy_u8EnableValue == MADC_ENABLE) {
		SET_BIT(ADC1->CR1, MADC_CR1_JAUTO_BIT);
	} else {
		CLR_BIT(ADC1->CR1, MADC_CR1_JAUTO_BIT);
	}
}

/**************************************************************************/
/* Func. Name: MADC_vSetExternalTrigger                                   */
/* i/p arguments: Copy_u8Group: MADC_<Group>_GROUP                        */
/* i/p arguments: Copy_u8TriggeringEdge: MADC_TRIG_EDGE_<Triggering Edge> */
/* i/p arguments: Copy_u8TriggerSource: MADC_EVENT_TRIG_<Group>_<Source>  */
/* o/p arguments: nothing                                                 */
/* Desc. : This API Enables External Triggering Source for Selected Group */
/**************************************************************************/
void MADC_vSetExternalTrigger(u8 Copy_u8Group, u8 Copy_u8TriggeringEdge, u8 Copy_u8TriggerSource) {
	if (Copy_u8Group == MADC_REGULAR_GROUP) {
		WRITE_BITS(ADC1->CR2, Copy_u8TriggeringEdge, TWO_BITS, MADC_CR2_EXTEN0_BIT);
		WRITE_BITS(ADC1->CR2, Copy_u8TriggerSource, FOUR_BITS, MADC_CR2_EXTSEL0_BIT);
	} else {
		WRITE_BITS(ADC1->CR2, Copy_u8TriggeringEdge, TWO_BITS, MADC_CR2_JEXTEN0_BIT);
		WRITE_BITS(ADC1->CR2, Copy_u8TriggerSource, FOUR_BITS, MADC_CR2_JEXTSEL0_BIT);
	}
}

/****************************************************************/
/* Func. Name: MADC_vEnableInjectedInterrupt                    */
/* i/p arguments: Copy_u8Group: MADC_<Group>_GROUP			    */
/* i/p arguments: Copy_u8EnableValue: MADC_<Enable or Disable>  */
/* o/p arguments: nothing                                       */
/* Desc. : This API Sets or Resets Interrupt for Selected Group */
/****************************************************************/
void MADC_vSetInterrupt(u8 Copy_u8Group, u8 Copy_u8EnableValue) {
	if (Copy_u8Group == MADC_REGULAR_GROUP) {
		if (Copy_u8EnableValue == MADC_ENABLE) { SET_BIT(ADC1->CR1, MADC_CR1_EOCIE_BIT); }
		else						  { CLR_BIT(ADC1->CR1, MADC_CR1_EOCIE_BIT); }
	} else {
		if (Copy_u8EnableValue == MADC_ENABLE) { SET_BIT(ADC1->CR1, MADC_CR1_JEOCIE_BIT); }
		else						  { CLR_BIT(ADC1->CR1, MADC_CR1_JEOCIE_BIT); }
	}
}

/************************************************************************/
/* Func. Name: MADC_vSetSamplingTime                                    */
/* i/p arguments: Channel: MADC_CHANNEL<Number>		 	                */
/* i/p arguments: Copy_u8SampleTime: MADC_SAMPLING_CYCLES_<Number>      */
/* o/p arguments: nothing                                               */
/* Desc. : This API Sets the Sample Time in Clocks for Selected Channel */
/************************************************************************/
void MADC_vSetSamplingTime(MADC_CHANNEL Channel, u8 Copy_u8SampleTime) {
	WRITE_BITS(ADC1->SMPR[1 - (Channel % 10)], Copy_u8SampleTime, THREE_BITS, ((Channel % 10) + 3));
}

/****************************************************************/
/* Func. Name: MADC_vSetNumberOfConversions                     */
/* i/p arguments: Copy_u8Group: MADC_<Group>_GROUP			    */
/* i/p arguments: Copy_u8Conversions: MADC_<Number>_CONVERSIONS	*/
/* o/p arguments: nothing                                       */
/* Desc. : This API Sets the Number of Channels to be Converted */
/****************************************************************/
void MADC_vSetNumberOfConversions(u8 Copy_u8Group, u8 Copy_u8Conversions) {
	if (Copy_u8Group == MADC_REGULAR_GROUP) {
		WRITE_BITS(ADC1->SQR[0], Copy_u8Conversions, FOUR_BITS, MADC_SQR1_L0_BIT);
	} else {
		WRITE_BITS(ADC1->JSQR, Copy_u8Conversions, TWO_BITS, MADC_JSQR_JL0_BIT);
	}
}

/************************************************************************************/
/* Func. Name: MADC_vSetSequence                                                    */
/* i/p arguments: Copy_u8Group: MADC_<Group>_GROUP			                        */
/* i/p arguments: Channel: MADC_CHANNEL<Number>		 	                            */
/* i/p arguments: Copy_u8SeqNumber: MADC_SEQUENCE_<Number>	                        */
/* o/p arguments: nothing                                                           */
/* Desc. : This API Sets the Selected Channel to be in a Specific Sequence Location */
/************************************************************************************/
void MADC_vSetSequence(u8 Copy_u8Group, MADC_CHANNEL Channel, u8 Copy_u8SeqNumber) {
	if (Copy_u8Group == MADC_REGULAR_GROUP) {
		if (Copy_u8SeqNumber <= MADC_SEQUENCE_6) {
			WRITE_BITS(ADC1->SQR[2], Channel, FIVE_BITS, Copy_u8SeqNumber * 5);
		} else if (Copy_u8SeqNumber <= MADC_SEQUENCE_12) {
			WRITE_BITS(ADC1->SQR[1], Channel, FIVE_BITS, (Copy_u8SeqNumber - MADC_SEQUENCE_7) * 5);
		} else {
			WRITE_BITS(ADC1->SQR[0], Channel, FIVE_BITS, (Copy_u8SeqNumber - MADC_SEQUENCE_13) * 5);
		}
	} else {
		WRITE_BITS(ADC1->JSQR, Channel, FIVE_BITS, Copy_u8SeqNumber * 5);
	}
}

