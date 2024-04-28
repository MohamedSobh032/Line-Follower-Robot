/******************************************************/
/* SWC: DMA Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v1.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of DMA            */
/******************************************************/
/* Header File Guard */
#ifndef _MDMA_PRIVATE_H_
#define _MDMA_PRIVATE_H_

/**********************************************/
/*              SxCR BITS Mapping             */
/**********************************************/
/* Enable Bit */
#define MDMA_SxCR_EN_BIT		0
/* Direct Mode Interrupt */
#define MDMA_SxCR_DMEIE_BIT		1
/* Perhiperal Flow Controller Bit */
#define MDMA_SxCR_PFCTRL_BIT	5
/* Direction Bits */
#define MDMA_SxCR_DIR0_BIT		6
#define MDMA_SxCR_DIR1_BIT		7
/* Circular Mode Bit */
#define MDMA_SxCR_CIRC_BIT		8
/* Peripheral Increment Mode */
#define MDMA_SxCR_PINC_BIT		9
/* Memory Increment Mode */
#define MDMA_SxCR_MINC_BIT		10
/* Peripheral Data Size */
#define MDMA_SxCR_PSIZE0_BIT	11
#define MDMA_SxCR_PSIZE1_BIT	12
/* Memory Data Size */
#define MDMA_SxCR_MSIZE0_BIT	13
#define MDMA_SxCR_MSIZE1_BIT	14
/* Priority Levels */
#define MDMA_SxCR_PL0_BIT		16
#define MDMA_SxCR_PL1_BIT		17
/* Peripheral Burst Transfer Configuration */
#define MDMA_SxCR_PBURST0_BIT	21
#define MDMA_SxCR_PBURST1_BIT	22
/* Memory Burst Transfer Configuration */
#define MDMA_SxCR_MBURST0_BIT	23
#define MDMA_SxCR_MBURST1_BIT	24
/* Channel Selection */
#define MDMA_SxCR_CHSEL0_BIT	25
#define MDMA_SxCR_CHSEL1_BIT	26
#define MDMA_SxCR_CHSEL2_BIT	27


/**********************************************/
/*             SxFCR BITS Mapping             */
/**********************************************/
/* FIFO Threshold Selection */
#define MDMA_SxFCR_FTH0_BIT		0
#define MDMA_SxFCR_FTH1_BIT		1
/* Direct Mode Disable Bit */
#define MDMA_SxFCR_DMDIS_BIT 	2



#endif /* _MDMA_PRIVATE_H_ */
