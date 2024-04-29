/******************************************************/
/* SWC: USART Driver                                  */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of USART          */
/******************************************************/

#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"
#include "MUSART_Config.h"
#include "MUSART_Interface.h"
#include "MUSART_Private.h"

void (*MUSART1_CallBack)(void) = (void*)0;
void (*MUSART2_CallBack)(void) = (void*)0;
void (*MUSART6_CallBack)(void) = (void*)0;


/***********************************************************************/
/* Func. Name: MUSART_vInit                                            */
/* i/p arguemnts: A_InitStruct: Contains the USART Settings            */
/* i/p arguemnts: A_ClockInitStruct: Contains the USART Clock Settings */
/* i/p arguemnts: USARTx: USART1, USART2, USART6    				   */
/* o/p arguments: nothing                              				   */
/* Desc. : This API initializes USARTx with Specifications 			   */
/***********************************************************************/
void MUSART_vInit(USART_t* USARTx, MUSART_InitTypeDef* A_InitStruct, MUSART_ClockInitTypeDef* A_ClockInitStruct) {
	/* Set The Baudrate */
	switch (A_InitStruct->Oversampling)
	{
		case MUSART_OVER_SAMPLING_16: USARTx->BRR = MUSART_BRR_SAMPLING16(__MUSART_PCLK__, A_InitStruct->BaudRate); break;
		case MUSART_OVER_SAMPLING_8:  USARTx->BRR = MUSART_BRR_SAMPLING8(__MUSART_PCLK__, A_InitStruct->BaudRate);  break;
	}
	/* Set The Control Register */
	USARTx->CR1 = (A_InitStruct->Oversampling << MUSART_CR1_OVER8_BIT)     |
			      (A_InitStruct->HardwareFlowControl << MUSART_CR1_UE_BIT) |
				  (A_InitStruct->DataWidth << MUSART_CR1_M_BIT)            |
				  (A_InitStruct->Parity_Enable << MUSART_CR1_PCE_BIT)      |
				  (A_InitStruct->Parity_Selection << MUSART_CR1_PS_BIT)    ;
	/* Set The Direction of Transferring Data */
	WRITE_BITS(USARTx->CR1, A_InitStruct->TransferDirection, TWO_BITS, MUSART_CR1_RE_BIT);
	/* Set The Second Control Register */
	USARTx->CR2 =   (A_InitStruct->StopBits << MUSART_CR2_STOP_BIT)				   |
					(A_ClockInitStruct->ClockOutput << MUSART_CR2_CLKEN_BIT)       |
					(A_ClockInitStruct->ClockPhase << MUSART_CR2_CPHA_BIT)         |
					(A_ClockInitStruct->ClockPolarity << MUSART_CR2_CPOL_BIT)      |
					(A_ClockInitStruct->LastBitClockPulse << MUSART_CR2_LBCL_BIT)  ;
	/* Clear The Status Register */
	USARTx->SR = 0;
}

/*************************************************/
/* Func. Name: MUSART_vEnable                    */
/* i/p arguemnts: USARTx: USART1, USART2, USART6 */
/* o/p arguments: nothing                        */
/* Desc. : This API Enables USARTx  			 */
/*************************************************/
void MUSART_vEnable(USART_t* USARTx)
{ SET_BIT(USARTx->CR1,MUSART_CR1_UE_BIT); }

/*************************************************/
/* Func. Name: MUSART_vDisable                   */
/* i/p arguemnts: USARTx: USART1, USART2, USART6 */
/* o/p arguments: nothing                        */
/* Desc. : This API Disables USARTx  			 */
/*************************************************/
void MUSART_vDisable(USART_t* USARTx)
{ CLR_BIT(USARTx->CR1,MUSART_CR1_UE_BIT); }

/******************************************************/
/* Func. Name: MUSART_u32EnableRxDMA                  */
/* i/p arguemnts: USARTx: USART1, USART2, USART6      */
/* o/p arguments: nothing                             */
/* Desc. : This API Enables USARTx Receiving with DMA */
/******************************************************/
volatile u32* MUSART_u32EnableRxDMA(USART_t* USARTx) {
	SET_BIT(USARTx->CR3, MUSART_CR3_DMAR_BIT);
	return &(USARTx->DR);
}

/******************************************************/
/* Func. Name: MUSART_vTransmitByte                   */
/* i/p arguemnts: USARTx: USART1, USART2, USART6      */
/* i/p arguemnts: Copy_u8Byte: Byte to be Transmitted */
/* o/p arguments: nothing                             */
/* Desc. : This API Transmit Byte using USARTx 		  */
/******************************************************/
void MUSART_vTransmitByte(USART_t* USARTx, u8 Copy_u8Byte) {
	while (GET_BIT(USARTx->SR, MUSART_SR_TXE_BIT) == 0);
	USARTx->DR= Copy_u8Byte;
	while (GET_BIT(USARTx->SR, MUSART_SR_TC_BIT) == 0);
	CLR_BIT(USARTx->SR, MUSART_SR_TC_BIT);
}

/**********************************************************/
/* Func. Name: MUSART_vTransmitString                     */
/* i/p arguemnts: USARTx: USART1, USART2, USART6          */
/* i/p arguemnts: Copy_u8String: String to be Transmitted */
/* o/p arguments: nothing                                 */
/* Desc. : This API Transmit String using USARTx 		  */
/**********************************************************/
void MUSART_vTransmitString(USART_t* USARTx, u8* Copy_u8String) {
	u8 Local_u8Counter = 0;
	while (Copy_u8String[Local_u8Counter] != '\0') {
		MUSART_vTransmitByte(USARTx, Copy_u8String[Local_u8Counter]);
		Local_u8Counter++;
	}
}

/****************************************************/
/* Func. Name: MUSART_u8ReceiveByteSynchNonBlocking */
/* i/p arguments: USARTx: USART1, USART2, USART6    */
/* o/p arguments: Recieved Data                     */
/* Desc. : This API Receives Data using USARTx      */
/****************************************************/
u8 MUSART_u8ReceiveByteSynchNonBlocking(USART_t* USARTx, u8* Copy_u8Data) {
	/* If there is data, return it */
	if (GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)) { *Copy_u8Data = USARTx->DR; return 1; }
	return 0;
}

/***************************************************************/
/* Func. Name: MUSART_u8ReceiveStringSynchNonBlocking          */
/* i/p arguments: USARTx: USART1, USART2, USART6      		   */
/* o/p arguments: Copy_u8String: Received String               */
/* Desc. : This API Receives String With Blocking using USARTx */
/***************************************************************/
void MUSART_vReceiveStringSynchNonBlocking(USART_t* USARTx, u8* Copy_u8String) {
	u8 Local_u8Counter = 0;
	u8 Local_u8DataRecieved = 0;
	while(MUSART_u8ReceiveByteSynchNonBlocking(USARTx, &Local_u8DataRecieved))
	{
		Copy_u8String[Local_u8Counter] = Local_u8DataRecieved;
		Local_u8Counter++;
	}
	Copy_u8String[Local_u8Counter] = '\0';
}

/********************************************************/
/* Func. Name: MUSART_u8ReceiveByteSynchBlocking        */
/* i/p arguments: USARTx: USART1, USART2, USART6        */
/* o/p arguments: Recieved Data                         */
/* Desc. : This API Receives With Blocking using USARTx */
/********************************************************/
u8 MUSART_u8ReceiveByteSynchBlocking(USART_t* USARTx, u8* Copy_u8Data) {
	u32 Local_u32TimeOut = 0;
	/* Iterate untill recieving is complete, or untill timeout */
	while ((!GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)) && (Local_u32TimeOut < MUSART_THRESHOLD_VALUE)) { Local_u32TimeOut++; }
	/* return 255 if timeout, else return the recieved data */
	if (Local_u32TimeOut == MUSART_THRESHOLD_VALUE) { return 0; }
	else { *Copy_u8Data = USARTx->DR; return 1; }
}

/***************************************************************/
/* Func. Name: MUSART_vReceiveStringSynchBlocking       	   */
/* i/p arguments: USARTx: USART1, USART2, USART6      		   */
/* o/p arguments: Copy_u8String: Received String               */
/* Desc. : This API Receives String With Blocking using USARTx */
/***************************************************************/
void MUSART_vReceiveStringSynchBlocking(USART_t* USARTx, u8* Copy_u8String) {
	u8 Local_u8Counter = 0;
	u8 Local_u8DataRecieved = 0;
	while(MUSART_u8ReceiveByteSynchBlocking(USARTx,&Local_u8DataRecieved))
	{
		Copy_u8String[Local_u8Counter] = Local_u8DataRecieved;
		Local_u8Counter++;
	}
	Copy_u8String[Local_u8Counter] = '\0';
}

/******************************************************/
/* Func. Name: MUSART_u8ReadDataRegister              */
/* i/p arguments: USARTx: USART1, USART2, USART6      */
/* o/p arguments: Data Register                       */
/* Desc. : This API Reads the Data Register of USARTx */
/******************************************************/
u8 MUSART_u8ReadDataRegister(USART_t* USARTx)
{ return USARTx -> DR; }

/*************************************************/
/* Func. Name: MUSART_vClearFlags                */
/* i/p arguments: USARTx: USART1, USART2, USART6 */
/* o/p arguments: nothing                        */
/* Desc. : This API Clears the flags of USARTx   */
/*************************************************/
void MUSART_vClearFlags(USART_t* USARTx)
{ USARTx -> SR = 0; }

/*****************************************************/
/* Func. Name: MUSART_vRxIntStatus                	 */
/* i/p arguments: USARTx: USART1, USART2, USART6 	 */
/* i/p arguments: Copy_u8Status: ENABLE, DISABLE 	 */
/* o/p arguments: nothing                        	 */
/* Desc. : This API Set the interrupt flag of USARTx */
/*****************************************************/
void MUSART_vRxIntStatus(USART_t* USARTx, u8 Copy_u8Status) {
	switch (Copy_u8Status)
	{
		case MUSART_ENABLE:  SET_BIT(USARTx->CR1,MUSART_CR1_RXNEIE_BIT); break;
		case MUSART_DISABLE: CLR_BIT(USARTx->CR1,MUSART_CR1_RXNEIE_BIT); break;
		default: break;
	}
}

/*************************************************************/
/* Func. Name: MUSARTx_vSetCallBack         	 			 */
/* i/p arguments: ptr: Pointer to function to be called back */
/* o/p arguments: nothing                        	     	 */
/* Desc. : This API Set the call backs of the interrupts 	 */
/*************************************************************/
void MUSART1_vSetCallBack(void (*ptr)(void))
{ MUSART1_CallBack = ptr; }
void MUSART2_vSetCallBack(void (*ptr)(void))
{ MUSART2_CallBack = ptr; }
void MUSART6_vSetCallBack(void (*ptr)(void))
{ MUSART6_CallBack = ptr; }


void USART1_IRQHandler(void) {
	USART1->SR = 0;
	MUSART1_CallBack();
}

void USART2_IRQHandler(void) {
	USART2->SR = 0;
	MUSART2_CallBack();
}

void USART6_IRQHandler(void) {
	USART6->SR = 0;
	MUSART6_CallBack();
}
