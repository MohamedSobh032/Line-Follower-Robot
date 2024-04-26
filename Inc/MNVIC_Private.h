/******************************************************/
/* SWC: NVIC Driver                                   */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of NVIC           */
/******************************************************/
/* Header File Guard */
#ifndef _MNVIC_PRIVATE_H_
#define _MNVIC_PRIVATE_H_

/**********************************************/
/*           NVIC Register Structure          */
/**********************************************/
#pragma pack(push, 1)
typedef struct {
    volatile u32 ISER[32];
    volatile u32 ICER[32];
    volatile u32 ISPR[32];
    volatile u32 ICPR[32];
    volatile u32 IABR[32];
    volatile u32  RES[32];
    volatile u8  IPR[240];
}NVIC_t;
#pragma pack(pop)

/**********************************************/
/*           NVIC Structure Pointer           */
/**********************************************/
/* NVIC Base Address 0xE000E100 */
#define NVIC        ((NVIC_t*)0xE000E100)

/* SCB Base Address 0xE000ED00 */
#define SCB_AIRCR   *((volatile u32*)0xE000ED0C)


/**********************************************/
/*            PRIORITY CONFIGURATION          */
/**********************************************/
#define MNVIC_PRIORITY_SIXTEEN_GROUPS_ZERO_SUBGROUPS	0b011
#define MNVIC_PRIORITY_EIGHT_GROUPS_TWO_SUBGROUPS		0b100
#define MNVIC_PRIORITY_FOUR_GROUPS_FOUR_SUBGROUPS		0b101
#define MNVIC_PRIORITY_TWO_GROUPS_EIGHT_SUBGROUPS		0b110
#define MNVIC_PRIORITY_ZERO_GROUPS_SIXTEEN_SUBGROUPS	0b111

#define VECT_KEY        0x05FA0000

#endif /* _MNVIC_PRIVATE_H_ */
