/******************************************************/
/* SWC: NVIC Driver                                   */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of NVIC           */
/******************************************************/
/* Header File Guard */
#ifndef _MNVIC_INTERFACE_H_
#define _MNVIC_INTERFACE_H_

void MNVIC_vInit(void);
void MNVIC_vSetPeripheralInterruptPriority(u8 Copy_u8PeripheralID, u8 Copy_u8GroupID, u8 Copy_u8SubGroupID);

void MNVIC_vEnablePeripheralInterrupt(u8 Copy_u8PeripheralID);
void MNVIC_vDisablePeripheralInterrupt(u8 Copy_u8PeripheralID);

void MNVIC_vSetPendingFlag(u8 Copy_u8PeripheralID);
void MNVIC_vClearPendingFlag(u8 Copy_u8PeripheralID);

#endif /* _MNVIC_INTERFACE_H_ */
