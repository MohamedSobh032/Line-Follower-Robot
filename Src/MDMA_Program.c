/******************************************************/
/* SWC: DMA Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of DMA            */
/******************************************************/
#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"

#include "MDMA_Private.h"
#include "MDMA_Config.h"
#include "MDMA_Interface.h"

/*************************************************************/
/* Func. Name: MDMA_vDirectInit			     			     */
/* i/p arguments: DMAx: DMA1, DMA2             				 */
/* i/p arguments: Copy_u8Stream: MDMA_STREAM_[Stream Number] */
/* i/p arguments: A_InitStruct: Initialization Structure     */
/* o/p arguments: nothing              						 */
/* Desc. : This API Initializes DMA to Direct Mode  		 */
/*************************************************************/
void MDMA_vDirectInit(DMA_t* DMAx, u8 Copy_u8Stream, MDMA_DirectInitType* A_InitStruct) {
	/* Disable DMA Stream */
	CLR_BIT(DMAx->S[Copy_u8Stream].CR, MDMA_SxCR_EN_BIT);
	/* Enable Direct Mode */
	CLR_BIT(DMAx->S[Copy_u8Stream].FCR, MDMA_SxFCR_DMDIS_BIT);
	/* Set the Transfer Direction */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR, A_InitStruct->TransferDirection, TWO_BITS, MDMA_SxCR_DIR0_BIT);
	/* Set the Peripheral Mode */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR, A_InitStruct->PINC, ONE_BIT, MDMA_SxCR_PINC_BIT);
	/* Set the Memory Mode */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR, A_InitStruct->MINC, ONE_BIT, MDMA_SxCR_MINC_BIT);
	/* Set the Priority */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR, A_InitStruct->PriorityLevel, TWO_BITS, MDMA_SxCR_PL0_BIT);
	/* Set the Channel */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR, A_InitStruct->Channel, THREE_BITS, MDMA_SxCR_CHSEL0_BIT);
	/* Set Peripheral Control */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR, A_InitStruct->PeripheralControl, ONE_BIT, MDMA_SxCR_PFCTRL_BIT);
	/* Set Circular Mode */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR, A_InitStruct->Circ, ONE_BIT, MDMA_SxCR_CIRC_BIT);
}

/*************************************************************/
/* Func. Name: MDMA_vBurstInit	 	    			         */
/* i/p arguments: DMAx: DMA1, DMA2             				 */
/* i/p arguments: Copy_u8Stream: MDMA_STREAM_[Stream Number] */
/* i/p arguments: A_InitStruct: Initialization Structure     */
/* o/p arguments: nothing              						 */
/* Desc. : This API Initializes DMA to Burst Mode	  		 */
/*************************************************************/
void MDMA_vBurstInit(DMA_t* DMAx, u8 Copy_u8Stream, MDMA_BurstInitType* A_InitStruct) {
	/* Disable DMA Stream */
	CLR_BIT(DMAx->S[Copy_u8Stream].CR,MDMA_SxCR_EN_BIT);
	/* Enable Burst Mode */
	SET_BIT(DMAx->S[Copy_u8Stream].FCR,MDMA_SxFCR_DMDIS_BIT);
	/* Set the Transfer Direction */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR,A_InitStruct->TransferDirection,TWO_BITS,MDMA_SxCR_DIR0_BIT);
	/* Set the Peripheral Mode */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR,A_InitStruct->PINC,ONE_BIT,MDMA_SxCR_PINC_BIT);
	/* Set the Memory Mode */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR,A_InitStruct->MINC,ONE_BIT,MDMA_SxCR_MINC_BIT);
	/* Set the Priority */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR,A_InitStruct->PriorityLevel,TWO_BITS,MDMA_SxCR_PL0_BIT);
	/* Set the Peripheral Burst Transfer Configuration */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR,A_InitStruct->PBurst,TWO_BITS,MDMA_SxCR_PBURST0_BIT);
	/* Set the Memory Burst Transfer Configuration */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR,A_InitStruct->MBurst,TWO_BITS,MDMA_SxCR_MBURST0_BIT);
	/* Set the Channel */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR,A_InitStruct->Channel,THREE_BITS,MDMA_SxCR_CHSEL0_BIT);
	/* Set the FIFO Size */
	WRITE_BITS(DMAx->S[Copy_u8Stream].FCR,A_InitStruct->FIFOSize,TWO_BITS,MDMA_SxFCR_FTH0_BIT);
}

/*************************************************************/
/* Func. Name: MDMA_vDMAStart	     		                 */
/* i/p arguments: DMAx: DMA1, DMA2             				 */
/* i/p arguments: Copy_u8Stream: MDMA_STREAM_<Stream Number> */
/* i/p arguments: A_TransferStruct: Transfer Structure       */
/* o/p arguments: nothing              						 */
/* Desc. : This API Starts Data Transfer Through DMAx        */
/*************************************************************/
void MDMA_vStart(DMA_t* DMAx, u8 Copy_u8Stream, MDMA_TransferStruct* A_TransferStruct) {
	/* Set the Data Sizes of the Memory and Peripheral */
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR, A_TransferStruct->Size, TWO_BITS, MDMA_SxCR_PSIZE0_BIT);
	WRITE_BITS(DMAx->S[Copy_u8Stream].CR, A_TransferStruct->Size, TWO_BITS, MDMA_SxCR_MSIZE0_BIT);
	/* Set the Source & Destination & Length */
	DMAx->S[Copy_u8Stream].PAR = (u32)A_TransferStruct->SrcAddr;
	DMAx->S[Copy_u8Stream].M0AR = (u32)A_TransferStruct->DstAddr;
	DMAx->S[Copy_u8Stream].NDTR = A_TransferStruct->Length;
	/* DMA Start */
	SET_BIT(DMAx->S[Copy_u8Stream].CR, MDMA_SxCR_EN_BIT);
}

