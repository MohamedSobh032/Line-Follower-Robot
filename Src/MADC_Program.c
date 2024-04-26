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

/**************************************/
/* Func. Name: MADC_vEnableScanMode   */
/* i/p arguments: nothing             */
/* o/p arguments: nothing             */
/* Desc. : This API Enables Scan Mode */
/**************************************/
void MADC_vEnableScanMode(void) {
	SET_BIT(ADC1->CR1, MADC_CR1_SCAN_BIT);
}

/***************************************************************************/
/* Func. Name: MADC_vEnableDiscontinuousMode                               */
/* i/p arguments: Copy_u8Group: MADC_<Group>_GROUP                         */
/* i/p arguments: Copy_u8DiscontinousNumber: MADC_DISCONT_<Number>_CHANNEL */
/* o/p arguments: nothing                                                  */
/* Desc. : This API Enables Discontinuous Mode for Selected Group          */
/***************************************************************************/
void MADC_vEnableDiscontinuousMode(u8 Copy_u8Group, u8 Copy_u8DiscontinousNumber) {
	if (Copy_u8Group == MADC_REGULAR_GROUP) { SET_BIT(ADC1->CR1, MADC_CR1_DISCEN_BIT); }
	else 									{ SET_BIT(ADC1->CR1, MADC_CR1_JDISCEN_BIT); }
	WRITE_BITS(ADC1->CR1, Copy_u8DiscontinousNumber, THREE_BITS, MADC_CR1_DISCNUM0_BIT);
}

/***********************************************************/
/* Func. Name: MADC_vEnableContinuousMode                  */
/* i/p arguments: nothing                                  */
/* o/p arguments: nothing                                  */
/* Desc. : This API Enables continuous Mode for all Groups */
/***********************************************************/
void MADC_vEnableContinuousMode(void) {
	/* Clear all Discontinuous bits */
	CLR_BIT(ADC1->CR1, MADC_CR1_DISCEN_BIT);
	CLR_BIT(ADC1->CR1, MADC_CR1_JDISCEN_BIT);
	/* Set Continuous bit */
	SET_BIT(ADC1->CR2, MADC_CR2_CONT_BIT);
}

/***********************************************************/
/* Func. Name: MADC_vEnableAutomaticInjection              */
/* i/p arguments: nothing                                  */
/* o/p arguments: nothing                                  */
/* Desc. : This API Enables Automatic Injected Conversions */
/***********************************************************/
void MADC_vEnableAutomaticInjection(void) {
	SET_BIT(ADC1->CR1, MADC_CR1_JAUTO_BIT);
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

void MADC_vEnableInjectedInterrupt(void) {

}

void MADC_vEnableRegularInterrupt(void);

void MADC_vSetSamplingTime(u8 Copy_u8Channel, u8 Copy_u8SampleTime);

void MADC_vSetNumberOfConversions(u8 Copy_u8Conversions);

void MADC_vSetSequence(u8 Copy_u8Group, u8 Copy_u8SeqNumber, u8 Copy_u8Channel);

