/******************************************************/
/* SWC: BIT MATH                                      */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of BIT MATH       */
/******************************************************/
/* Header Guard File */
#ifndef _LBIT_MATH_H_
#define _LBIT_MATH_H_

#define SET_BIT(REG_NAME, BIT_NUM)				      			REG_NAME = REG_NAME | (1 << BIT_NUM)
#define CLR_BIT(REG_NAME, BIT_NUM)      			  			REG_NAME = REG_NAME & (~(1 << BIT_NUM))
#define TOG_BIT(REG_NAME, BIT_NUM)      			  			REG_NAME = REG_NAME ^ (1 << BIT_NUM)
#define GET_BIT(REG_NAME, BIT_NUM)      			  			((REG_NAME >> BIT_NUM) & 1)
#define WRITE_BITS(REG_NAME, VALUE, NUM_OF_BITS, START_BIT) 	REG_NAME = ((u32)(VALUE << START_BIT)) | (REG_NAME & (~((u32)(NUM_OF_BITS << START_BIT))))

typedef enum {
	ONE_BIT       = 0x0001,
	TWO_BITS      = 0x0003,
	THREE_BITS    = 0x0007,
	FOUR_BITS     = 0x000F,
	FIVE_BITS     = 0x001F,
	SIX_BITS      = 0x003F,
	SEVEN_BTIS    = 0x007F,
	EIGHT_BITS    = 0x00FF,
	NINE_BITS     = 0x01FF,
	TEN_BITS      = 0x03FF,
	ELEVEN_BITS   = 0x07FF,
	TWELVE_BITS   = 0x0FFF,
	THIRTEEN_BITS = 0x1FFF,
	FOURTEEN_BITS = 0x3FFF,
	FIFTEEN_BITS  = 0x7FFF,
	SIXTEEN_BITS  = 0xFFFF,
} BIT_SIZE;

#endif /* _LBIT_MATH_H_ */
