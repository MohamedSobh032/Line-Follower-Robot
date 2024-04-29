/******************************************************/
/* SWC: NVIC Driver                                   */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of NVIC           */
/******************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"

#include "MNVIC_Private.h"
#include "MNVIC_Config.h"
#include "MNVIC_Interface.h"

/*************************************/
/* Func. Name: MNVIC_vInit           */
/* i/p arguments: Nothing            */
/* o/p arguments: Nothing            */
/* Desc. : This API initializes NVIC */
/*************************************/
void MNVIC_vInit(void) {
	SCB_AIRCR = VECT_KEY | (_MNVIC_PRIORITY_CONFIGURATION_ << 8);
}

/********************************************************************/
/* Func. Name: MNVIC_vSetPeripheralInterruptPriority                */
/* i/p arguments: Copy_u8PeripheralID: The Peripheral to be Changed */
/* i/p arguments: GroupID                                           */
/* i/p arguments: SubGroupID                                        */
/* o/p arguments: Nothing                                           */
/* Desc. : This API Sets a Peripheral to a Group and Subgroup       */
/********************************************************************/
void MNVIC_vSetPeripheralInterruptPriority(u8 Copy_u8PeripheralID, MNVIC_GROUP GroupID, MNVIC_SUBGROUP SubGroupID) {
	u8 Local_u8Priority;
	switch (_MNVIC_PRIORITY_CONFIGURATION_) {
		case MNVIC_PRIORITY_SIXTEEN_GROUPS_ZERO_SUBGROUPS: Local_u8Priority = GroupID; 									  break;
		case MNVIC_PRIORITY_EIGHT_GROUPS_TWO_SUBGROUPS:    Local_u8Priority = (GroupID << 1) | (ONE_BIT    & SubGroupID); break;
		case MNVIC_PRIORITY_FOUR_GROUPS_FOUR_SUBGROUPS:    Local_u8Priority = (GroupID << 2) | (TWO_BITS   & SubGroupID); break;
		case MNVIC_PRIORITY_TWO_GROUPS_EIGHT_SUBGROUPS:    Local_u8Priority = (GroupID << 3) | (THREE_BITS & SubGroupID); break;
		case MNVIC_PRIORITY_ZERO_GROUPS_SIXTEEN_SUBGROUPS: Local_u8Priority = (GroupID << 4) | (FOUR_BITS  & SubGroupID); break;
		default: break;
	}
    NVIC->IPR[Copy_u8PeripheralID] = Local_u8Priority << 4;
}

/**************************************************************/
/* Func. Name: MNVIC_vEnablePeripheralInterrupt               */
/* i/p arguments: Copy_u8PeripheralID                         */
/* o/p arguments: Nothing                                     */
/* Desc. : This API enables interrupt for specific Peripheral */
/**************************************************************/
void MNVIC_vEnablePeripheralInterrupt(u8 Copy_u8PeripheralID) {
	NVIC->ISER[(Copy_u8PeripheralID / 32)] = 1 << (Copy_u8PeripheralID % 32);
	NVIC->ICER[(Copy_u8PeripheralID / 32)] = 0 << (Copy_u8PeripheralID % 32);
}

/***************************************************************/
/* Func. Name: MNVIC_vDisablePeripheralInterrupt               */
/* i/p arguments: Copy_u8PeripheralID                          */
/* o/p arguments: Nothing                                      */
/* Desc. : This API disables interrupt for specific Peripheral */
/***************************************************************/
void MNVIC_vDisablePeripheralInterrupt(u8 Copy_u8PeripheralID) {
	NVIC->ISER[(Copy_u8PeripheralID / 32)] = 0 << (Copy_u8PeripheralID % 32);
	NVIC->ICER[(Copy_u8PeripheralID / 32)] = 1 << (Copy_u8PeripheralID % 32);
}

/******************************************************************/
/* Func. Name: MNVIC_vSetPendingFlag                              */
/* i/p arguments: Copy_u8PeripheralID                             */
/* o/p arguments: Nothing                                         */
/* Desc. : This API Set the Pending Flag of a specific Peripheral */
/******************************************************************/
void MNVIC_vSetPendingFlag(u8 Copy_u8PeripheralID) {
	NVIC->ISPR[(Copy_u8PeripheralID / 32)] = 1 << (Copy_u8PeripheralID % 32);
	NVIC->ICPR[(Copy_u8PeripheralID / 32)] = 0 << (Copy_u8PeripheralID % 32);
}

/********************************************************************/
/* Func. Name: MNVIC_vClearPendingFlag                              */
/* i/p arguments: Copy_u8PeripheralID                               */
/* o/p arguments: Nothing                                           */
/* Desc. : This API Clear the Pending Flag of a specific Peripheral */
/********************************************************************/
void MNVIC_vClearPendingFlag(u8 Copy_u8PeripheralID) {
	NVIC->ISPR[(Copy_u8PeripheralID / 32)] = 0 << (Copy_u8PeripheralID % 32);
	NVIC->ICPR[(Copy_u8PeripheralID / 32)] = 1 << (Copy_u8PeripheralID % 32);
}
