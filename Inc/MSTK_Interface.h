/******************************************************/
/* SWC: STK Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of STK            */
/******************************************************/
/* Header File Guard */
#ifndef _MSTK_INTERFACE_H_
#define _MSTK_INTERFACE_H_

void MSTK_vInit(void);
void MSTK_vDisable(void);
void MSTK_vBusyWait(u32 Copy_u32Ticks);
void MSTK_vSingleCall(u32 Copy_u32Ticks, void (*LpF)(void));
void MSTK_vPeriodicCall(u32 Copy_u32Ticks, void (*LpF)(void));
u32 MSTK_u32GetElapsedTime(void);
u32 MSTK_u32GetRemainingTime(void);

#endif /* _MSTK_INTERFACE_H_ */
