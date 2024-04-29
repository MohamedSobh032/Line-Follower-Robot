/******************************************************/
/* SWC: DMA Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of DMA            */
/******************************************************/
/* Header File Guard */
#ifndef _MDMA_INTERFACE_H_
#define _MDMA_INTERFACE_H_

/**********************************************/
/*            DMA Stream Structure            */
/**********************************************/
typedef struct {
	volatile u32 CR;
	volatile u32 NDTR;
	volatile u32 PAR;
	volatile u32 M0AR;
	volatile u32 M1AR;
	volatile u32 FCR;
}DMA_STREAM_t;

/**********************************************/
/*           DMA Register Structure           */
/**********************************************/
typedef struct {
	volatile u32 LISR;
	volatile u32 HISR;
	volatile u32 LIFCR;
	volatile u32 HIFCR;
	volatile DMA_STREAM_t S[8];
}DMA_t;

/**********************************************/
/*           DMA Structure Pointers           */
/**********************************************/
#define DMA1		((DMA_t*) 0x40026000)
#define DMA2		((DMA_t*) 0x40026400)

typedef struct {
	u8 PeripheralControl;
	u8 TransferDirection;
	u8 Circ;
	u8 PINC;
	u8 MINC;
	u8 PriorityLevel;
	u8 Channel;
} MDMA_DirectInitType;

typedef struct {
	u8 TransferDirection;
	u8 PINC;
	u8 MINC;
	u8 PriorityLevel;
	u8 PBurst;
	u8 MBurst;
	u8 Channel;
	u8 FIFOSize;
} MDMA_BurstInitType;

typedef struct {
	u32* SrcAddr;
	u32* DstAddr;
	u16 Length;
	u8 Size;
} MDMA_TransferStruct;


void MDMA_vDirectInit(DMA_t* DMAx, u8 Copy_u8Stream, MDMA_DirectInitType* A_InitStruct);
void MDMA_vBurstInit(DMA_t* DMAx, u8 Copy_u8Stream, MDMA_BurstInitType* A_InitStruct);

void MDMA_vStart(DMA_t* DMAx, u8 Copy_u8Stream, MDMA_TransferStruct* A_TransferStruct);



/**********************************************/
/*               Stream Numbers               */
/**********************************************/
#define MDMA_STREAM_0		0
#define MDMA_STREAM_1		1
#define MDMA_STREAM_2		2
#define MDMA_STREAM_3		3
#define MDMA_STREAM_4		4
#define MDMA_STREAM_5		5
#define MDMA_STREAM_6		6
#define MDMA_STREAM_7		7

/**********************************************/
/*          Transfer Direction Types          */
/**********************************************/
#define MDMA_DIRECTION_PER_MEM		0b00
#define MDMA_DIRECTION_MEM_PER		0b01
#define MDMA_DIRECTION_MEM_MEM		0b10

/**********************************************/
/*     Memory | Peripheral Increment Mode     */
/**********************************************/
#define MDMA_INCREMENT_FIXED		0b0
#define MDMA_INCREMENT_SIZE			0b1

/**********************************************/
/*        Memory | Peripheral Data Size       */
/**********************************************/
#define MDMA_SIZE_BYTE			0b00
#define MDMA_SIZE_HWORD			0b01
#define MDMA_SIZE_WORD			0b10

/**********************************************/
/*               Priority Level               */
/**********************************************/
#define MDMA_PRIORITY_LOW		0b00
#define MDMA_PRIORITY_MEDIUM	0b01
#define MDMA_PRIORITY_HIGH		0b10
#define MDMA_PRIORITY_VHIGH		0b11

/**********************************************/
/*   Memory | Peripheral Burst Configuration  */
/**********************************************/
#define MDMA_BURST_INCR1		0b00
#define MDMA_BURST_INCR4		0b01
#define MDMA_BURST_INCR8		0b10
#define MDMA_BURST_INCR16		0b11

/**********************************************/
/*               Channel Numbers              */
/**********************************************/
#define MDMA_CHANNEL_0		0b000
#define MDMA_CHANNEL_1		0b001
#define MDMA_CHANNEL_2		0b010
#define MDMA_CHANNEL_3		0b011
#define MDMA_CHANNEL_4		0b100
#define MDMA_CHANNEL_5		0b101
#define MDMA_CHANNEL_6		0b110
#define MDMA_CHANNEL_7		0b111

/**********************************************/
/*                 FIFO Sizes                 */
/**********************************************/
#define MDMA_FIFO_QUARTER		0b00
#define MDMA_FIFO_HALF			0b01
#define MDMA_FIFO_THIRD			0b10
#define MDMA_FIFO_FULL			0b11

/**********************************************/
/*                 DMA Status                 */
/**********************************************/
#define MDMA_DISABLE		0
#define MDMA_ENABLE			1


#endif /* _MDMA_INTERFACE_H_ */
