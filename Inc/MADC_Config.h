/******************************************************/
/* SWC: ADC Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of ADC            */
/******************************************************/
/* Header File Guard */
#ifndef _MADC_CONFIG_H_
#define _MADC_CONFIG_H_

#define MADC_CLOCK_PRESCALER				MADC_CLK_DIV_BY_4

#define MADC_RESOLUTION						MADC_RESOLUTION_12_BITS

#define MADC_DATA_ALLIGNMENT				MADC_ALLIGN_RIGHT

#define MADC_REGULAR_CONVERSION_MODE		MADC_CONTINUOUS_CONVERSION
#define MADC_INJECTED_CONVERSION_MODE		MADC_CONTINUOUS_CONVERSION

#if MADC_REGULAR_CONVERSION_MODE == MADC_DISCONTINUOUS_CONVERSION || MADC_INJECTED_CONVERSION_MODE == MADC_DISCONTINUOUS_CONVERSION
	#define MADC_DISCONTINUOUS_LENGTH		3
#endif

#define MADC_AUTOMATIC_INJECTION			MADC_DISABLE

#define MADC_SCANNING_MODE					MADC_SINGLE_CONVERSION_MODE

#if MADC_SCANNING_MODE == MADC_SCAN_CONVERSION_MODE
	#define MADC_END_OF_CONVERSION_LOCATION		MADC_EOC_REGULAR_SEQUENCE_END
#endif

#define MADC_REGULAR_EXTERNAL_TRIGGER		MADC_DISABLE
#define MADC_INJECTED_EXTERNAL_TRIGGER		MADC_DISABLE

#if MADC_REGULAR_EXTERNAL_TRIGGER == MADC_ENABLE
	#define MADC_REGULAR_EXTERNAL_TRIGGER_EDGE		MADC_TRIG_EDGE_RISING
	#define MADC_REGULAR_EXTERNAL_TRIGGER_SOURCE	MADC_EVENT_TRIG_REGULAR_TIM1CC1
#endif

#if MADC_INJECTED_EXTERNAL_TRIGGER == MADC_ENABLE
	#define MADC_INJECTED_EXTERNAL_TRIGGER_EDGE		MADC_TRIG_EDGE_RISING
	#define MADC_INJECTED_EXTERNAL_TRIGGER_SOURCE	MADC_EVENT_TRIG_INJECTED_TIM1CC4
#endif

#define MADC_SET_AWD_ON_REGULAR		MADC_DISABLE
#define MADC_SET_AWD_ON_INJECTED	MADC_DISABLE



#endif /* _MADC_CONFIG_H_ */
