/******************************************************/
/* SWC: USART Driver                                  */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of USART          */
/******************************************************/
/* Header File Guard */
#ifndef _MUSART_INTERFACE_H_
#define _MUSART_INTERFACE_H_


/**********************************************/
/*          USART Register Structure          */
/**********************************************/
typedef struct {
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}USART_t;

/**********************************************/
/*           USART Structure Pointer          */
/**********************************************/
#define USART1 			((USART_t*) 0x40011000)
#define USART2 			((USART_t*) 0x40004400)
#define USART6 			((USART_t*) 0x40011400)

typedef struct {
	u32 BaudRate;
	u8  DataWidth;
	u8  StopBits;
	u8  Parity_Enable;
	u8  Parity_Selection;
	u8  TransferDirection;
	u8  HardwareFlowControl;
	u8  Oversampling;
}MUSART_InitTypeDef;

typedef struct {
	u8 ClockOutput;
	u8 ClockPolarity;
	u8 ClockPhase;
	u8 LastBitClockPulse;
}MUSART_ClockInitTypeDef;


void MUSART_vInit(USART_t* USARTx, MUSART_InitTypeDef* A_InitStruct, MUSART_ClockInitTypeDef* A_ClockInitStruct);
void MUSART_vEnable(USART_t* USARTx);
void MUSART_vDisable(USART_t* USARTx);

volatile u32* MUSART_u32EnableRxDMA(USART_t* USARTx);

void MUSART_vTransmitByte(USART_t* USARTx, u8 Copy_u8Byte);
void MUSART_vTransmitString(USART_t* USARTx, u8* Copy_u8String);

u8 MUSART_u8ReceiveByteSynchNonBlocking(USART_t* USARTx, u8* Copy_u8Data);
void MUSART_vReceiveStringSynchNonBlocking(USART_t* USARTx, u8* Copy_u8String);

u8 MUSART_u8ReceiveByteSynchBlocking(USART_t* USARTx, u8* Copy_u8Data);
void MUSART_vReceiveStringSynchBlocking(USART_t* USARTx, u8* Copy_u8String);

u8 MUSART_u8ReadDataRegister(USART_t* USARTx);
void MUSART_vClearFlags(USART_t* USARTx);
void MUSART_vRxIntStatus(USART_t* USARTx, u8 Copy_u8Status);

void MUSART1_vSetCallBack(void (*ptr)(void));
void MUSART2_vSetCallBack(void (*ptr)(void));
void MUSART6_vSetCallBack(void (*ptr)(void));

/**********************************************/
/*                USART Status                */
/**********************************************/
#define MUSART_DISABLE						0
#define MUSART_ENABLE						1

/**********************************************/
/*             Over Sampling Types            */
/**********************************************/
#define MUSART_OVER_SAMPLING_16				0
#define MUSART_OVER_SAMPLING_8 				1

/**********************************************/
/*        Communication Direction Type        */
/**********************************************/
#define MUSART_DIRECTION_TX             	0b10
#define MUSART_DIRECTION_RX             	0b01
#define MUSART_DIRECTION_TX_RX          	0b11

/**********************************************/
/*                Parity Types                */
/**********************************************/
#define MUSART_PARITY_EVEN       			0
#define MUSART_PARITY_ODD        			1

/**********************************************/
/*               Datawidth Size               */
/**********************************************/
#define MUSART_DATAWIDTH_8BIT				0
#define MUSART_DATAWIDTH_9BIT				1

/**********************************************/
/*                Stopbit Size                */
/**********************************************/
#define MUSART_STOP_ONE_BIT					0
#define MUSART_STOP_HALF_BIT				1
#define MUSART_STOP_TWO_BIT					2
#define MUSART_STOP_ONE_HALF_BIT			3

#endif /* MUSART_INTERFACE_H_ */
