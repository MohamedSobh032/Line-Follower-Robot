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

/**********************************************/
/*             PRIORITY GROUP IDs             */
/**********************************************/
typedef enum {
	MNVIC_GROUP_ZERO     = 0,
	MNVIC_GROUP_ONE      = 1,
	MNVIC_GROUP_TWO      = 2,
	MNVIC_GROUP_THREE    = 3,
	MNVIC_GROUP_FOUR     = 4,
	MNVIC_GROUP_FIVE     = 5,
	MNVIC_GROUP_SIX      = 6,
	MNVIC_GROUP_SEVEN    = 7,
	MNVIC_GROUP_EIGHT    = 8,
	MNVIC_GROUP_NINE     = 9,
	MNVIC_GROUP_TEN      = 10,
	MNVIC_GROUP_ELEVEN   = 11,
	MNVIC_GROUP_TWELVE   = 12,
	MNVIC_GROUP_THIRTEEN = 13,
	MNVIC_GROUP_FOURTEEN = 14,
	MNVIC_GROUP_FIFTEEN  = 15
} MNVIC_GROUP;

/**********************************************/
/*           PRIORITY SUB GROUP IDs           */
/**********************************************/
typedef enum {
	MNVIC_SUBGROUP_ZERO     = 0,
	MNVIC_SUBGROUP_ONE      = 1,
	MNVIC_SUBGROUP_TWO      = 2,
	MNVIC_SUBGROUP_THREE    = 3,
	MNVIC_SUBGROUP_FOUR     = 4,
	MNVIC_SUBGROUP_FIVE     = 5,
	MNVIC_SUBGROUP_SIX      = 6,
	MNVIC_SUBGROUP_SEVEN    = 7,
	MNVIC_SUBGROUP_EIGHT    = 8,
	MNVIC_SUBGROUP_NINE     = 9,
	MNVIC_SUBGROUP_TEN      = 10,
	MNVIC_SUBGROUP_ELEVEN   = 11,
	MNVIC_SUBGROUP_TWELVE   = 12,
	MNVIC_SUBGROUP_THIRTEEN = 13,
	MNVIC_SUBGROUP_FOURTEEN = 14,
	MNVIC_SUBGROUP_FIFTEEN  = 15
} MNVIC_SUBGROUP;


void MNVIC_vInit(void);
void MNVIC_vSetPeripheralInterruptPriority(u8 Copy_u8PeripheralID, MNVIC_GROUP GroupID, MNVIC_SUBGROUP SubGroupID);

void MNVIC_vEnablePeripheralInterrupt(u8 Copy_u8PeripheralID);
void MNVIC_vDisablePeripheralInterrupt(u8 Copy_u8PeripheralID);

void MNVIC_vSetPendingFlag(u8 Copy_u8PeripheralID);
void MNVIC_vClearPendingFlag(u8 Copy_u8PeripheralID);


#endif /* _MNVIC_INTERFACE_H_ */
