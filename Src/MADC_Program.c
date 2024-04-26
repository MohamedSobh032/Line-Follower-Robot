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
#include "MADC_Interface.h"
#include "MADC_Config.h"
/*****************************************************/
/* Func. Name: MADC_vGeneralInit                     */
/* i/p arguments: nothing                            */
/* o/p arguments: nothing                            */
/* Desc. : This API Initializes General ADC Settings */
/*****************************************************/
void MADC_vGeneralInit(void) {
	/* Set the Prescaler of the ADC CLK */
	WRITE_BITS(ADC_CCR, MADC_CLOCK_PRESCALER, TWO_BITS, MADC_CCR_ADCPRE0_BIT);
	/* Set the Data Allignment */
	if (MADC_DATA_ALLIGNMENT == MADC_ALLIGN_RIGHT) { CLR_BIT(ADC1->CR2, MADC_CR2_ALLIGN_BIT); }
	else 										   { SET_BIT(ADC1->CR2, MADC_CR2_ALLIGN_BIT); }
	/* Set the Resolution of the ADC */
	WRITE_BITS(ADC1->CR1, MADC_RESOLUTION, TWO_BITS, MADC_CR1_RES0_BIT);
	/* Clear Status Register */
	ADC1->SR = 0;
	/* Set the Conversion Mode of Regular Group */
	#if MADC_REGULAR_CONVERSION_MODE == MADC_NORMAL_CONVERSION
		CLR_BIT(ADC1->CR1, MADC_CR1_DISCEN_BIT);
		CLR_BIT(ADC1->CR2, MADC_CR2_CONT_BIT);
	#elif  MADC_REGULAR_CONVERSION_MODE == MADC_CONTINUOUS_CONVERSION
		CLR_BIT(ADC1->CR1, MADC_CR1_DISCEN_BIT);
		SET_BIT(ADC1->CR2, MADC_CR2_CONT_BIT);
	#elif MADC_REGULAR_CONVERSION_MODE == MADC_DISCONTINUOUS_CONVERSION
		SET_BIT(ADC1->CR1, MADC_CR1_DISCEN_BIT);
		CLR_BIT(ADC1->CR2, MADC_CR2_CONT_BIT);
		WRITE_BITS(ADC1->CR1, MADC_DISCONTINUOUS_LENGTH, THREE_BITS, MADC_CR1_DISCNUM0_BIT);
	#endif
	/* Set the Conversion Mode of Injected Group */
	#if MADC_INJECTED_CONVERSION_MODE == MADC_NORMAL_CONVERSION
		CLR_BIT(ADC1->CR1, MADC_CR1_JDISCEN_BIT);
		CLR_BIT(ADC1->CR2, MADC_CR2_CONT_BIT);
	#elif  MADC_INJECTED_CONVERSION_MODE == MADC_CONTINUOUS_CONVERSION
		CLR_BIT(ADC1->CR1, MADC_CR1_JDISCEN_BIT);
		SET_BIT(ADC1->CR2, MADC_CR2_CONT_BIT);
	#elif MADC_INJECTED_CONVERSION_MODE == MADC_DISCONTINUOUS_CONVERSION
		SET_BIT(ADC1->CR1, MADC_CR1_JDISCEN_BIT);
		CLR_BIT(ADC1->CR2, MADC_CR2_CONT_BIT);
		WRITE_BITS(ADC1->CR1, MADC_DISCONTINUOUS_LENGTH, THREE_BITS, MADC_CR1_DISCNUM0_BIT);
	#endif

	/* Set the Scanning Mode */
	#if MADC_SCANNING_MODE == MADC_SINGLE_CONVERSION_MODE
		CLR_BIT(ADC1->CR1, MADC_CR1_SCAN_BIT);
		/* Clear the EOC After Each Regular Conversion (BY DEFAULT IT IS SINGLE CONVERSION) */
		CLR_BIT(ADC1->CR2, MADC_CR2_EOCS_BIT);
	#elif MADC_SCANNING_MODE == MADC_SCAN_CONVERSION_MODE
		SET_BIT(ADC1->CR1, MADC_CR1_SCAN_BIT);
		if (MADC_END_OF_CONVERSION_LOCATION == MADC_EOC_REGULAR_SEQUENCE_END) { CLR_BIT(ADC1->CR2, MADC_CR2_EOCS_BIT); }
		else																  { SET_BIT(ADC1->CR2, MADC_CR2_EOCS_BIT); }
	#endif

	#if MADC_REGULAR_EXTERNAL_TRIGGER == MADC_ENABLE
		WRITE_BITS(ADC1->CR2, MADC_REGULAR_EXTERNAL_TRIGGER_EDGE, TWO_BITS, MADC_CR2_EXTEN0_BIT);
		WRITE_BITS(ADC1->CR2, MADC_REGULAR_EXTERNAL_TRIGGER_SOURCE, FOUR_BITS, MADC_CR2_EXTSEL0_BIT);
	#else
		WRITE_BITS(ADC1->CR2, MADC_TRIG_EDGE_DISABLED, TWO_BITS, MADC_CR2_EXTEN0_BIT);
	#endif

	#if MADC_INJECTED_EXTERNAL_TRIGGER == MADC_ENABLE
		WRITE_BITS(ADC1->CR2, MADC_INJECTED_EXTERNAL_TRIGGER_EDGE, TWO_BITS, MADC_CR2_JEXTEN0_BIT);
		WRITE_BITS(ADC1->CR2, MADC_INJECTED_EXTERNAL_TRIGGER_SOURCE, FOUR_BITS, MADC_CR2_JEXTSEL0_BIT);
	#else
		WRITE_BITS(ADC1->CR2, MADC_TRIG_EDGE_DISABLED, TWO_BITS, MADC_CR2_JEXTEN0_BIT);
	#endif

	/* Set Automatic Injection */
	if (MADC_AUTOMATIC_INJECTION == MADC_ENABLE) { SET_BIT(ADC1->CR1, MADC_CR1_JAUTO_BIT); }
	else										 { CLR_BIT(ADC1->CR1, MADC_CR1_JAUTO_BIT); }

	/* Set ADC to Power Down Mode */
	CLR_BIT(ADC1->CR2, MADC_CR2_ADON_BIT);
}

/**********************************************************/
/* Func. Name: MADC_vAWDInit                              */
/* i/p arguments: A_InitStruct: AWD Initialization Struct */
/* o/p arguments: nothing                                 */
/* Desc. : This API Initializes AWD Settings              */
/**********************************************************/
void MADC_vAWDInit(MADC_AWDTypeDef* A_InitStruct) {
	/* Set AWD on Regular */
	#if MADC_SET_AWD_ON_REGULAR == MADC_ENABLE
		SET_BIT(ADC1->CR1, MADC_CR1_AWDEN_BIT);
	#else
		CLR_BIT(ADC1->CR1, MADC_CR1_AWDEN_BIT);
	#endif
	/* Set AWD on Injected */
	#if MADC_SET_AWD_ON_INJECTED == MADC_ENABLE
		SET_BIT(ADC1->CR1, MADC_CR1_JAWDEN_BIT);
	#else
		CLR_BIT(ADC1->CR1, MADC_CR1_JAWDEN_BIT);
	#endif

	WRITE_BITS(ADC1->CR1, A_InitStruct->SingleOrMultiple, ONE_BIT, MADC_CR1_AWDSGL_BIT);
	if (GET_BIT(ADC1->CR1, MADC_CR1_SCAN_BIT)) {
		if (A_InitStruct->SingleOrMultiple == MADC_AWD_SINGLE_CHANNEL_SCAN) {
			WRITE_BITS(ADC1->CR1, A_InitStruct->Channel, FIVE_BITS, MADC_CR1_AWDCH0_BIT);
		}
	}
	WRITE_BITS(ADC1->HTR, A_InitStruct->HighThreshold, TWELVE_BITS, 0);
	WRITE_BITS(ADC1->LTR, A_InitStruct->LowThreshold, TWELVE_BITS, 0);
}

/*************************************/
/* Func. Name: MADC_vEnable          */
/* i/p arguments: nothing            */
/* o/p arguments: nothing            */
/* Desc. : This API Wakes up the ADC */
/*************************************/
void MADC_vEnable(u8 Copy_u8EnableReg, u8 Copy_u8EnableInj) {
	/* Wake up ADC from Power Down Mode */
	SET_BIT(ADC1->CR2, MADC_CR2_ADON_BIT);
	if (Copy_u8EnableReg == MADC_ENABLE) {
		SET_BIT(ADC1->CR2, MADC_CR2_SWSTART_BIT);
	}
	if (Copy_u8EnableInj == MADC_ENABLE) {
		SET_BIT(ADC1->CR2, MADC_CR2_JSWSTART_BIT);
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

/*******************************************************************************/
/* Func. Name: MADC_u16ReadSingleConversion                                    */
/* i/p arguments: nothing			                                           */
/* o/p arguments: nothing                                                      */
/* Desc. : This API Waits for ADC to convert, then Returns the Data            */
/* NOTE  : Use This Function Only if ADC is Working on Single Conversion Mode  */
/*******************************************************************************/
u16 MADC_u16ReadSingleConversion(void) {
	/* Wait for ADC to Finish Conversion */
	while (!GET_BIT(ADC1->SR, MADC_SR_EOC_BIT));
	return (u16)ADC1->DR;
}

