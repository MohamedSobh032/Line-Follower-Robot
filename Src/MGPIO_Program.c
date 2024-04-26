/******************************************************/
/* SWC: GPIO Driver                                   */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of GPIO           */
/******************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MGPIO_Config.h"
#include "MGPIO_Private.h"
#include "MGPIO_Interface.h"

/******************************************************************/
/* Func. Name: MGPIO_vSetPinMode                                  */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                      */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15       */
/* i/p arguments: Copy_u8Mode: MGPIO_MODE_<Mode Type>             */
/* o/p arguments: nothing                                         */
/* Desc. : This API Allows User to Set the mode of a Specific Pin */
/******************************************************************/
void MGPIO_vSetPinMode(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin, u8 Copy_u8Mode) {
    /* i/p Validation */
    if (Copy_u8Mode > MGPIO_MODE_ANALOG) { return; /* Do Nothing */ }
    WRITE_BITS(GPIOx->MODER, Copy_u8Mode, TWO_BITS, Copy_GPIOPin * 2);
}

/*************************************************************************/
/* Func. Name: MGPIO_vSetPinOutputType                                   */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                             */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15              */
/* i/p arguments: Copy_u8Type: MGPIO_OUTPUT_TYPE_<Output Type>           */
/* o/p arguments: nothing                                                */
/* Desc. : This API Allows User to Set the Output Type of a Specific Pin */
/*************************************************************************/
void MGPIO_vSetPinOutputType(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin, u8 Copy_u8OType) {
    /* i/p Validation */
    if (Copy_u8OType > MGPIO_OUTPUT_TYPE_OD) { return; /* Do Nothing */ }
    WRITE_BITS(GPIOx->OTYPER, Copy_u8OType, ONE_BIT, Copy_GPIOPin);
}

/**************************************************************************/
/* Func. Name: MGPIO_vSetPinOutputSpeed                                */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                              */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15               */
/* i/p arguments: Copy_u8Speed: MGPIO_<Speed>_SPEED                       */
/* o/p arguments: nothing                                                 */
/* Desc. : This API Allows User to Set the Output Speed of a Specific Pin */
/**************************************************************************/
void MGPIO_vSetPinOutputSpeed(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin, u8 Copy_u8Speed) {
    /* i/p Validation */
    if (Copy_u8Speed > MGPIO_VHIGH_SPEED) { return; /* Do Nothing */ }
    WRITE_BITS(GPIOx->OSPEEDR, Copy_u8Speed, TWO_BITS, Copy_GPIOPin * 2);
}

/************************************************************************/
/* Func. Name: MGPIO_vSetPinInputType                                   */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                            */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15             */
/* i/p arguments: Copy_u8IType: MGPIO_INPUT_TYPE_<Input Type>           */
/* o/p arguments: nothing                                               */
/* Desc. : This API Allows User to Set the Input Type of a Specific Pin */
/************************************************************************/
void MGPIO_vSetPinInputType(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin, u8 Copy_u8IType) {
    /* i/p Validation */
    if (Copy_u8IType > MGPIO_INPUT_TYPE_PULLDOWN) { return; /* Do Nothing */ }
    WRITE_BITS(GPIOx->PUPDR, Copy_u8IType, TWO_BITS, Copy_GPIOPin * 2);
}

/******************************************************************************/
/* Func. Name: MGPIO_vSetPinAFDirection                                    */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                                  */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15                   */
/* i/p arguments: Copy_GPIOPinDirection: MGPIO_AF00 --> MGPIO_AF15            */
/* o/p arguments: nothing                                                     */
/* Desc. : This API Allows User to Set the Direction of AF for a Specific Pin */
/******************************************************************************/
void MGPIO_vSetPinAFDirection(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin, MGPIO_AF Copy_GPIOAFDir) {
    if (Copy_GPIOPin <= MGPIO_PIN07) { WRITE_BITS(GPIOx->AFRL, Copy_GPIOAFDir, FOUR_BITS, Copy_GPIOPin * 4); }
    else		 					 { WRITE_BITS(GPIOx->AFRH, Copy_GPIOAFDir, FOUR_BITS, (Copy_GPIOPin - 8) * 4); }
}

/*******************************************************************/
/* Func. Name: MGPIO_vSetPinValue                                  */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                       */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15        */
/* i/p arguments: Copy_GPIOPinValue: MGPIO_OUTPUT_<Output Value>   */
/* o/p arguments: nothing                                          */
/* Desc. : This API Allows User to Set the Value of a Specific Pin */
/*******************************************************************/
void MGPIO_vSetPinValue(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin, u8 Copy_u8Value) {
    if      (Copy_u8Value == MGPIO_OUTPUT_HIGH) { SET_BIT(GPIOx->ODR, Copy_GPIOPin); }
    else if	(Copy_u8Value == MGPIO_OUTPUT_LOW)  { CLR_BIT(GPIOx->ODR, Copy_GPIOPin); }
}

/************************************************************************************/
/* Func. Name: MGPIO_vSetPartValue                              					*/
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                       					*/
/* i/p arguments: Copy_u16Data: Data to be Written        						    */
/* i/p arguments: Copy_BITSize: Size of the Data in Bits                            */
/* i/p arguments: Copy_GPIOPinStart: Start Bit                                      */
/* o/p arguments: nothing                                                           */
/* Desc. : This API Allows User to Set the Value of a Specific Part of the Register */
/************************************************************************************/
void MGPIO_vSetPartValue(GPIO_t* GPIOx, u16 Copy_u16Data, BIT_SIZE Copy_BITSize, MGPIO_PIN Copy_GPIOPinStart) {
	WRITE_BITS(GPIOx->ODR, Copy_u16Data, Copy_BITSize, Copy_GPIOPinStart);
}

/*******************************************************************/
/* Func. Name: MGPIO_vSetPinDirectAccess                           */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                       */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15        */
/* i/p arguments: Copy_GPIOPinValue: MGPIO_OUTPUT_DIRECT_<Value>   */
/* o/p arguments: nothing                                          */
/* Desc. : This API Allows User to Set the Value of a Specific Pin */
/*******************************************************************/
void MGPIO_vSetPinDirectAccess(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin, u8 Copy_u8Value) {
	GPIOx->BSRR = MGPIO_OUTPUT_HIGH << (Copy_GPIOPin + Copy_u8Value);
	GPIOx->BSRR = MGPIO_OUTPUT_LOW;
}

/**********************************************************************/
/* Func. Name: MGPIO_vTogglePinValue                                  */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                          */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15           */
/* o/p arguments: nothing                                             */
/* Desc. : This API Allows User to Toggle the Value of a Specific Pin */
/**********************************************************************/
void MGPIO_vTogglePinValue(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin) {
    TOG_BIT(GPIOx->ODR, Copy_GPIOPin);
}

/*******************************************************************/
/* Func. Name: MGPIO_u8GetPinValue                                 */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                       */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15        */
/* o/p arguments: The Value of the GPIO Pin                        */
/* Desc. : This API Allows User to Get the Value of a Specific Pin */
/*******************************************************************/
u8 MGPIO_u8GetPinValue(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin) {
    return GET_BIT(GPIOx->IDR, Copy_GPIOPin);
}

/********************************************************************/
/* Func. Name: MGPIO_bLockPin                                       */
/* i/p arguments: GPIOx: GPIOA, GPIOB, GPIOC                        */
/* i/p arguments: Copy_GPIOPin: MGPIO_PIN00 --> MGPIO_PIN15         */
/* o/p arguments: Could Lock or Not                                 */
/* Desc. : This API Blocks Configuring a Specific Port Untill Reset */
/********************************************************************/
bool MGPIO_bLockPin(GPIO_t* GPIOx, MGPIO_PIN Copy_GPIOPin) {
    volatile u32 tmp = 1 << MGPIO_LCKR_LCKK_BIT;
    /* Apply lock key write sequence */
    tmp |= 1 << Copy_GPIOPin;
    /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
    GPIOx->LCKR = tmp;
    /* Reset LCKx bit(s): LCKK='0' + LCK[15-0] */
    GPIOx->LCKR = 1 << Copy_GPIOPin;
    /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
    GPIOx->LCKR = tmp;
    /* Read LCKR register. This read is mandatory to complete key lock sequence */
    tmp = GPIOx->LCKR;
    if (GET_BIT(GPIOx->LCKR, MGPIO_LCKR_LCKK_BIT)) { return true; }
    else 										   { return false; }
}
