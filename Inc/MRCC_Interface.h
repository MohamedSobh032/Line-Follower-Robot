/******************************************************/
/* SWC: RCC Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of RCC            */
/******************************************************/
/* Header File Guard */
#ifndef _MRCC_INTERFACE_H_
#define _MRCC_INTERFACE_H_

/**********************************************/
/*          Peripheral Enable Busses          */
/**********************************************/
typedef enum {
	/* Default Busses */
	MRCC_BUS_AHB1   = 0,
	MRCC_BUS_AHB2   = 1,
	MRCC_BUS_APB1   = 2,
	MRCC_BUS_APB2   = 3,
	/* Low Power Busses */
	MRCC_BUS_AHB1LP = 4,
	MRCC_BUS_AHB2LP = 5,
	MRCC_BUS_APB1LP = 6,
	MRCC_BUS_APB2LP = 7
} MRCC_BUS;

/**********************************************/
/*              Peripheral Clocks             */
/**********************************************/
typedef enum {
	/* AHB1 Peripherals */
	MRCC_AHB1_GPIOAEN      = 0,
	MRCC_AHB1_GPIOBEN      = 1,
	MRCC_AHB1_GPIOCEN      = 2,
	MRCC_AHB1_CRCEN        = 12,
	MRCC_AHB1_DMA1EN       = 21,
	MRCC_AHB1_DMA2EN       = 22,
	/* AHB2 Peripherals */
	MRCC_AHB2_OTGFSEN      = 7,
	/* APB1 Peripherals */
	MRCC_APB1_TIM2EN       = 0,
	MRCC_APB1_TIM3EN       = 1,
	MRCC_APB1_TIM4EN       = 2,
	MRCC_APB1_TIM5EN       = 3,
	MRCC_APB1_WWDGEN       = 11,
	MRCC_APB1_SPI2EN       = 14,
	MRCC_APB1_SPI3EN       = 15,
	MRCC_APB1_USART2EN     = 17,
	MRCC_APB1_I2C1EN       = 21,
	MRCC_APB1_I2C2EN       = 22,
	MRCC_APB1_I2C3EN       = 23,
	MRCC_APB1_PWREN        = 28,
	/* APB2 Peripherals */
	MRCC_APB2_TIM1EN       = 0,
	MRCC_APB2_USART1EN     = 4,
	MRCC_APB2_USART6EN     = 5,
	MRCC_APB2_ADC1EN       = 8,
	MRCC_APB2_SDIOEN       = 11,
	MRCC_APB2_SPI1EN       = 12,
	MRCC_APB2_SPI4EN       = 13,
	MRCC_APB2_SYSCFGEN     = 14,
	MRCC_APB2_TIM9EN       = 16,
	MRCC_APB2_TIM10EN      = 17,
	MRCC_APB2_TIM11EN      = 18,
	/* AHB1LP Peripherals */
	MRCC_AHB1LP_GPIOALPEN  = 0,
	MRCC_AHB1LP_GPIOBLPEN  = 1,
	MRCC_AHB1LP_GPIOCLPEN  = 2,
	MRCC_AHB1LP_CRCLPEN    = 12,
	MRCC_AHB1LP_FLITFLPEN  = 15,
	MRCC_AHB1LP_SRAM1LPEN  = 16,
	MRCC_AHB1LP_DMA1LPEN   = 21,
	MRCC_AHB1LP_DMA2LPEN   = 22,
	/* AHB2LP Peripherals */
	MRCC_AHB2LP_OTGFSLPEN  = 7,
	/* APB1LP Peripherals */
	MRCC_APB1LP_TIM2LPEN   = 0,
	MRCC_APB1LP_TIM3LPEN   = 1,
	MRCC_APB1LP_TIM4LPEN   = 2,
	MRCC_APB1LP_TIM5LPEN   = 3,
	MRCC_APB1LP_WWDGLPEN   = 11,
	MRCC_APB1LP_SPI2LPEN   = 14,
	MRCC_APB1LP_SPI3LPEN   = 15,
	MRCC_APB1LP_USART2LPEN = 17,
	MRCC_APB1LP_I2C1LPEN   = 21,
	MRCC_APB1LP_I2C2LPEN   = 22,
	MRCC_APB1LP_I2C3LPEN   = 23,
	MRCC_APB1LP_PWRLPEN    = 28,
	/* APB2LP Peripherals */
	MRCC_APB2LP_TIM1LPEN   = 0,
	MRCC_APB2LP_USART1LPEN = 4,
	MRCC_APB2LP_USART6LPEN = 5,
	MRCC_APB2LP_ADC1LPEN   = 8,
	MRCC_APB2LP_SDIOLPEN   = 11,
	MRCC_APB2LP_SPI1LPEN   = 12,
	MRCC_APB2LP_SPI4LPEN   = 13,
	MRCC_APB2LP_SYSCFGLPEN = 14,
	MRCC_APB2LP_TIM9LPEN   = 16,
	MRCC_APB2LP_TIM10LPEN  = 17,
	MRCC_APB2LP_TIM11LPEN  = 18
} MRCC_PeriphClock;

/**********************************************/
/*             Function Prototypes            */
/**********************************************/
void MRCC_vInitSysAndBusClock(void);
void MRCC_vEnablePeriphClock(MRCC_BUS Copy_BusID, MRCC_PeriphClock Copy_PeriphID);
void MRCC_vDisablePeriphClock(MRCC_BUS Copy_BusID, MRCC_PeriphClock Copy_PeriphID);

#endif /* _MRCC_INTERFACE_H_ */
