/******************************************************/
/* SWC: RCC Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of RCC            */
/******************************************************/

#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"
#include "MRCC_Interface.h"
#include "MRCC_Config.h"
#include "MRCC_Private.h"

/******************************************************************/
/* Func. Name: MRCC_vInitSysAndBusClock 						  */
/* i/p arguments: nothing              	   						  */
/* o/p arguments: nothing              							  */
/* Desc. : This API Initializes the The System CLK and Busses CLK */
/******************************************************************/
void MRCC_vInitSysAndBusClock() {
	#if MRCC_SYSTEM_CLOCK_SOURCE == MRCC_HSI_CLK_SOURCE
		/* Enable HSI */
		SET_BIT(RCC_CR, MRCC_CR_HSION_BIT);
		/* Trim HSI */
		WRITE_BITS(RCC_CR, MRCC_HSI_TRIMMING, FIVE_BITS, MRCC_CR_HSITRIM_BIT);
		/* Switch System Clock to HSI */
		WRITE_BITS(RCC_CFGR, MRCC_SW_SWITCH_TO_HSI, TWO_BITS, MRCC_CFGR_SW_BIT);
		/* booling till HSI is Stable */
		while(!GET_BIT(RCC_CR, MRCC_CR_HSIRDY_BIT));
	#elif MRCC_SYSTEM_CLOCK_SOURCE == MRCC_HSE_CRYSTAL_CLK_SOURCE
		/* Set HSE as Crystal */
		CLR_BIT(RCC_CR, MRCC_CR_HSEBYP_BIT);
		/* Enable HSE */
		SET_BIT(RCC_CR, MRCC_CR_HSEON_BIT);
		/* Switch System Clock to HSE */
		WRITE_BITS(RCC_CFGR, MRCC_SW_SWITCH_TO_HSE, TWO_BITS, MRCC_CFGR_SW_BIT);
		/* booling till HSI is Stable */
		while(!GET_BIT(RCC_CR, MRCC_CR_HSERDY_BIT));
	#elif MRCC_SYSTEM_CLOCK_SOURCE == MRCC_HSE_USER_CLK_SOURCE
		/* Set HSE as Bypass */
		SET_BIT(RCC_CR, MRCC_CR_HSEBYP_BIT);
		/* Enable HSE */
		SET_BIT(RCC_CR, MRCC_CR_HSEON_BIT);
		/* Switch System Clock to HSE */
		WRITE_BITS(RCC_CFGR, MRCC_SW_SWITCH_TO_HSE, TWO_BITS, MRCC_CFGR_SW_BIT);
		/* booling till HSI is Stable */
		while(!GET_BIT(RCC_CR, MRCC_CR_HSERDY_BIT));
	#elif MRCC_SYSTEM_CLOCK_SOURCE == MRCC_PLL_HSI_CLK_SOURCE
		/* Enable HSI */
		SET_BIT(RCC_CR, MRCC_CR_HSION_BIT);
		/* Trim HSI */
		WRITE_BITS(RCC_CR, MRCC_HSI_TRIMMING, FIVE_BITS, MRCC_CR_HSITRIM_BIT);
		/* booling till HSI is Stable */
		while(!GET_BIT(RCC_CR, MRCC_CR_HSIRDY_BIT));
		/* Set the PLL Source to HSI */
		CLR_BIT(RCC_PLLCFGR, MRCC_PLLCFGR_PLLSRC_BIT);
		/* Set the Prescalers */
		WRITE_BITS(RCC_PLLCFGR, MRCC_PLL_P_DIV_FACTOR, TWO_BITS, MRCC_PLLCFGR_PLLP_BIT);
		WRITE_BITS(RCC_PLLCFGR,  MRCC_PLL_N_MUL_FACTOR, NINE_BITS, MRCC_PLLCFGR_PLLN_BIT);
		WRITE_BITS(RCC_PLLCFGR,MRCC_PLL_M_DIV_FACTOR, SIX_BITS, MRCC_PLLCFGR_PLLM_BIT);
		/* Enable PLL */
		SET_BIT(RCC_CR, MRCC_CR_PLLON_BIT);
		/* Switch System Clock to PLL */
		WRITE_BITS(RCC_CFGR, MRCC_SW_SWITCH_TO_PLL, TWO_BITS, MRCC_CFGR_SW_BIT);
		/* booling till HSI is Stable */
		while(!GET_BIT(RCC_CR, MRCC_CR_PLLRDY_BIT));
	#elif MRCC_SYSTEM_CLOCK_SOURCE == MRCC_PLL_HSE_CRYSTAL_CLK_SOURCE
		/* Set HSE as Crystal */
		CLR_BIT(RCC_CR, MRCC_CR_HSEBYP_BIT);
		/* Enable HSE */
		SET_BIT(RCC_CR, MRCC_CR_HSEON_BIT);
		/* booling till HSI is Stable */
		while(!GET_BIT(RCC_CR, MRCC_CR_HSERDY_BIT));
		/* Set the PLL Source to HSE */
		SET_BIT(RCC_PLLCFGR, MRCC_PLLCFGR_PLLSRC_BIT);
		/* Set the Prescalers */
		WRITE_BITS(RCC_PLLCFGR, MRCC_PLL_P_DIV_FACTOR, TWO_BITS, MRCC_PLLCFGR_PLLP_BIT);
		WRITE_BITS(RCC_PLLCFGR, MRCC_PLL_N_MUL_FACTOR, NINE_BITS, MRCC_PLLCFGR_PLLN_BIT);
		WRITE_BITS(RCC_PLLCFGR, MRCC_PLL_M_DIV_FACTOR, SIX_BITS, MRCC_PLLCFGR_PLLM_BIT);
		/* Enable PLL */
		SET_BIT(RCC_CR, MRCC_CR_PLLON_BIT);
		/* Switch System Clock to PLL */
		WRITE_BITS(RCC_CFGR, MRCC_SW_SWITCH_TO_PLL, TWO_BITS, MRCC_CFGR_SW_BIT);
		/* booling till HSI is Stable */
		while(!GET_BIT(RCC_CR, MRCC_CR_PLLRDY_BIT));
	#elif MRCC_SYSTEM_CLOCK_SOURCE == MRCC_PLL_HSE_USER_CLK_SOURCE
		/* Set HSE as Bypass */
		SET_BIT(RCC_CR, MRCC_CR_HSEBYP_BIT);
		/* Enable HSE */
		SET_BIT(RCC_CR, MRCC_CR_HSEON_BIT);
		/* booling till HSI is Stable */
		while(!GET_BIT(RCC_CR, MRCC_CR_HSERDY_BIT));
		/* Set the PLL Source to HSE */
		SET_BIT(RCC_PLLCFGR, MRCC_PLLCFGR_PLLSRC_BIT);
		/* Set the Prescalers */
		WRITE_BITS(RCC_PLLCFGR, MRCC_PLL_P_DIV_FACTOR, TWO_BITS, MRCC_PLLCFGR_PLLP_BIT);
		WRITE_BITS(RCC_PLLCFGR, MRCC_PLL_N_MUL_FACTOR, NINE_BITS, MRCC_PLLCFGR_PLLN_BIT);
		WRITE_BITS(RCC_PLLCFGR, MRCC_PLL_M_DIV_FACTOR, SIX_BITS, MRCC_PLLCFGR_PLLM_BIT);
		/* Enable PLL */
		SET_BIT(RCC_CR, MRCC_CR_PLLON_BIT);
		/* Switch System Clock to PLL */
		WRITE_BITS(RCC_CFGR, MRCC_SW_SWITCH_TO_PLL, TWO_BITS, MRCC_CFGR_SW_BIT);
		/* booling till HSI is Stable */
		while(!GET_BIT(RCC_CR, MRCC_CR_PLLRDY_BIT));
	#else
		#warning "Invalid Clock Source Configuration!"
	#endif
	/* Set the AHB Prescaler */
	WRITE_BITS(RCC_CFGR, MRCC_AHB_PRESCALER, FOUR_BITS, MRCC_CFGR_HPRE_BIT);
	/* Set the APB1 Prescaler */
	WRITE_BITS(RCC_CFGR, MRCC_APB1_PRESCALER, THREE_BITS, MRCC_CFGR_PPRE1_BIT);
	/* Set the APB2 Prescaler */
	WRITE_BITS(RCC_CFGR, MRCC_APB2_PRESCALER, THREE_BITS, MRCC_CFGR_PPRE2_BIT);
}

/*****************************************************************************/
/* Func. Name: MRCC_vEnablePeriphClock                                       */
/* i/p arguments: Copy_BusID: MRCC_BUS_AHB1 -->  MRCC_BUS_APB2LP             */
/* i/p arguments: Copy_PeriphID: <PeripheralName>EN || <PeripheralName>LPEN  */
/* o/p arguments: nothing                                                    */
/* Desc. : This API Allows the User to Enable CLK for a Specific Peripheral  */
/*****************************************************************************/
void MRCC_vEnablePeriphClock(MRCC_BUS Copy_BusID, MRCC_PeriphClock Copy_PeriphID) {
	switch (Copy_BusID) {
		case MRCC_BUS_AHB1:   SET_BIT(RCC_AHB1ENR, Copy_PeriphID);   break;
        case MRCC_BUS_AHB2:   SET_BIT(RCC_AHB2ENR, Copy_PeriphID);   break;
        case MRCC_BUS_APB1:   SET_BIT(RCC_APB1ENR, Copy_PeriphID);   break;
        case MRCC_BUS_APB2:   SET_BIT(RCC_APB2ENR, Copy_PeriphID);   break;
		case MRCC_BUS_AHB1LP: SET_BIT(RCC_AHB1LPENR, Copy_PeriphID); break;
        case MRCC_BUS_AHB2LP: SET_BIT(RCC_AHB2LPENR, Copy_PeriphID); break;
        case MRCC_BUS_APB1LP: SET_BIT(RCC_APB1LPENR, Copy_PeriphID); break;
        case MRCC_BUS_APB2LP: SET_BIT(RCC_APB2LPENR, Copy_PeriphID); break;
        default: break;
    }
}

/*****************************************************************************/
/* Func. Name: MRCC_vDisablePeriphClock                                      */
/* i/p arguments: Copy_BusID: MRCC_BUS_AHB1 -->  MRCC_BUS_APB2LP             */
/* i/p arguments: Copy_PeriphID: <PeripheralName>EN || <PeripheralName>LPEN  */
/* o/p arguments: nothing                                                    */
/* Desc. : This API Allows the User to Enable CLK for a Specific Peripheral  */
/*****************************************************************************/
void MRCC_vDisablePeriphClock(MRCC_BUS Copy_BusID, MRCC_PeriphClock Copy_PeriphID) {
	switch (Copy_BusID) {
		case MRCC_BUS_AHB1:   CLR_BIT(RCC_AHB1ENR, Copy_PeriphID);   break;
        case MRCC_BUS_AHB2:   CLR_BIT(RCC_AHB2ENR, Copy_PeriphID);   break;
        case MRCC_BUS_APB1:   CLR_BIT(RCC_APB1ENR, Copy_PeriphID);   break;
        case MRCC_BUS_APB2:   CLR_BIT(RCC_APB2ENR, Copy_PeriphID);   break;
		case MRCC_BUS_AHB1LP: CLR_BIT(RCC_AHB1LPENR, Copy_PeriphID); break;
        case MRCC_BUS_AHB2LP: CLR_BIT(RCC_AHB2LPENR, Copy_PeriphID); break;
        case MRCC_BUS_APB1LP: CLR_BIT(RCC_APB1LPENR, Copy_PeriphID); break;
        case MRCC_BUS_APB2LP: CLR_BIT(RCC_APB2LPENR, Copy_PeriphID); break;
        default: break;
    }
}
