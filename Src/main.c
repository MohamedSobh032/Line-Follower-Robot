/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MSTK_Interface.h"
#include "MNVIC_Interface.h"
#include "MRCC_Interface.h"
#include "MGPIO_Interface.h"
#include "MUSART_Interface.h"
#include "MADC_Interface.h"
#include "MGPT_Interface.h"
#include "MDMA_Interface.h"
#include "main.h"

/************************************ VARIABLE DEFINITIONS ************************************/
u16 APP_u16IRData[APP_IR_ARRAY_COUNT];		/* IR ARRAY CURRENT MEASURED VALUES          */
u16 APP_u16IRThreshold[APP_IR_ARRAY_COUNT];	/* IR ARRAY THRESHOLD VALUES                 */
u32 APP_s32SpeedLeft = 0;                   /* LEFT MOTOR SPEED IN TERMS OF PERIODICITY  */
u32 APP_s32SpeedRight = 0;                  /* RIGHT MOTOR SPEED IN TERMS OF PERIODICITY */
			/* MOBILE VARIABLES */
u8 APP_u8DirBuffer[APP_MOBILE_MSG_LEN];     /* DATA DIRECTION FROM MOBILE APPLICATION    */
u8 APP_u8Control;                           /* MOVEMENT CONTROL FROM MOBILE APPLICATION  */
			/*   PID VARIABLES   */
f32 APP_f32Kp, APP_f32Kd, APP_f32Ki;        /* PID CONTROLLER CONSTANTS                  */
s32 APP_s32Error, APP_s32PrevError = 0;     /* ERROR TO BE ACCUMULATED, DIFFERENTIATED   */
s32 APP_s32P, APP_s32I, APP_s32D;           /* PID CONTROL VARIABLES                     */
/**********************************************************************************************/



/************************************ FUNCTION DEFINITIONS ************************************/
void APP_vInit(void);                       /* INITIALIZATION FUNCTION                   */
void APP_vDriveMotors(APP_WHEEL_DIR Right_Dir,
				APP_WHEEL_DIR Left_Dir);    /* MOTOR DRIVER FUNCTION                     */
void APP_vCalibrateLineFollowing(void);     /* CALIBRATION TO GET THRESHOLD              */
void APP_vCalibrateMazeSolving(void);       /* CALIBRATION WITH MOBILE TO GET PATH       */
void APP_vReturnToPointZero(void);          /* RESET THE FACE DIRECTION OF THE CAR       */
void APP_vPIDcontrol(void);                 /* LINE FOLLOWING FUNCTION USING PID CONCEPT */
/**********************************************************************************************/



int main(void) {

	/*************************************** INITIALIZATION ***************************************/
	APP_vInit();
	/**********************************************************************************************/


	/********************************** CHOOSE WHICH CODE TO RUN **********************************/
	APP_ALGORITHM AlgorithmFlag = 0;
	while (true) {
		if (!MGPIO_u8GetPinValue(APP_BUTTON_APP1)) {
			AlgorithmFlag = APP_LINE_FOLLOWING;
			break;
		}
		if (!MGPIO_u8GetPinValue(APP_BUTTON_APP2)) {
			AlgorithmFlag = APP_MAZE_SOLVING;
			break;
		}
	}
	/**********************************************************************************************/


	/********************************** LINE FOLLOWING ALGORITHM **********************************/
	if (AlgorithmFlag == APP_LINE_FOLLOWING) {
		/* CALIBRATION OF LINE FOLLOWING */
		APP_vCalibrateLineFollowing();
		/* RETURN TO POINT ZERO */
		APP_vReturnToPointZero();
		while (true) {
			/* CONFLICT EXTREME RIGHT AND EXTREME LEFT --> (BLACK AT 0) && (BLACK AT 4) */
			if ((APP_u16IRData[0] < APP_u16IRThreshold[0]) &&
					(APP_u16IRData[APP_IR_ARRAY_COUNT - 1] < APP_u16IRThreshold[APP_IR_ARRAY_COUNT - 1])) {
				// TODO -- SHOULD KEEP FORWARD
				continue;
			}
			/* EXTREME RIGHT --> (WHITE AT 0 (IT IS WHITE HERE)) && (BLACK AT 4) */
			else if (APP_u16IRData[APP_IR_ARRAY_COUNT - 1] < APP_u16IRThreshold[APP_IR_ARRAY_COUNT - 1]) {
				APP_s32SpeedLeft = APP_CAR_MOVE_FULL_FORCE;
				APP_s32SpeedRight = APP_CAR_MOVE_ZERO_FORCE;
				APP_vDriveMotors(APP_CLOCK_WISE, APP_CLOCK_WISE);
				continue;
			}
			/* EXTREME LEFT --> (BLACK AT 0) && (WHITE AT 4 (IT IS WHITE HERE)) */
			else if (APP_u16IRData[0] < APP_u16IRThreshold[0]) {
				APP_s32SpeedLeft = APP_CAR_MOVE_ZERO_FORCE;
				APP_s32SpeedRight = APP_CAR_MOVE_FULL_FORCE;
				APP_vDriveMotors(APP_CLOCK_WISE, APP_CLOCK_WISE);
				continue;
			}
			/* NORMAL PID CONTROL */
			else if (APP_u16IRData[2] < APP_u16IRThreshold[2]) {
				// TODO -- SHOULD KEEP FORWARD
				continue;
			}
		}
	}
	/**********************************************************************************************/


	/*********************************** MAZE SOLVING ALGORITHM ***********************************/
	else if (AlgorithmFlag == APP_MAZE_SOLVING) {
		/* CALIBRATION FOR MAZE SOLVING */
		APP_vCalibrateMazeSolving();
		/* RETURN TO POINT ZERO */
		APP_vReturnToPointZero();
		// TODO -- IMPLEMENT MAZE SOLVING ALGORTHIM
	}
	/**********************************************************************************************/
}


/**
 * @brief Initialize the application.
 *
 * This function configures clock settings, enables necessary peripherals, configures pins,
 * initializes ADC, DMA, and PWM for car control.
 *
 * @param None
 * @return None
 */
void APP_vInit(void) {
	/********************* CLOCK CONFIGURATIONS AND BUSSES/PERIPHERALS ENABLE *********************/
	/* INIT CLOCK AND BUSSES CLOCK */
	MRCC_vInitSysAndBusClock();
	/* INIT ALL NEEDED PERIPHERALS CLOCK */
	MRCC_vEnablePeriphClock(MRCC_BUS_AHB1, MRCC_AHB1_GPIOAEN);
	MRCC_vEnablePeriphClock(MRCC_BUS_AHB1, MRCC_AHB1_GPIOBEN);
	MRCC_vEnablePeriphClock(MRCC_BUS_APB2, MRCC_APB2_ADC1EN);
	MRCC_vEnablePeriphClock(MRCC_BUS_AHB1, MRCC_AHB1_DMA2EN);
	MRCC_vEnablePeriphClock(MRCC_BUS_APB2, MRCC_APB2_USART1EN);
	MRCC_vEnablePeriphClock(MRCC_BUS_APB1, MRCC_APB1_TIM3EN);
	MRCC_vEnablePeriphClock(MRCC_BUS_APB1, MRCC_APB1_TIM4EN);
	/**********************************************************************************************/

	/********************** NESTED VECTOR INTERRUPT CONTROLLER CONFIGURATION **********************/
	MNVIC_vInit();
	/**********************************************************************************************/

	/************************************* PINS CONFIGURATION *************************************/
	/* INIT ANALOG READ PINS */
	MGPIO_vSetPinMode(APP_IR0, MGPIO_MODE_ANALOG);
	MGPIO_vSetPinMode(APP_IR1, MGPIO_MODE_ANALOG);
	MGPIO_vSetPinMode(APP_IR2, MGPIO_MODE_ANALOG);
	MGPIO_vSetPinMode(APP_IR3, MGPIO_MODE_ANALOG);
	MGPIO_vSetPinMode(APP_IR4, MGPIO_MODE_ANALOG);
	/* INIT USART TRANSMIT RECEIVE PINS */
	MGPIO_vSetPinMode(APP_MOBILE_USART_TX, MGPIO_MODE_ALTERNATE);
	MGPIO_vSetPinMode(APP_MOBILE_USART_RX, MGPIO_MODE_ALTERNATE);
	MGPIO_vSetPinAFDirection(APP_MOBILE_USART_TX, APP_MOBILE_USART_AF);
	MGPIO_vSetPinAFDirection(APP_MOBILE_USART_RX, APP_MOBILE_USART_AF);
	/* INIT TIMER PWM PIN */
	MGPIO_vSetPinMode(APP_TIM_PWM_R_PIN, MGPIO_MODE_ALTERNATE);
	MGPIO_vSetPinAFDirection(APP_TIM_PWM_R_PIN, APP_TIM_PWM_R_AF);
	MGPIO_vSetPinMode(APP_TIM_PWM_L_PIN, MGPIO_MODE_ALTERNATE);
	MGPIO_vSetPinAFDirection(APP_TIM_PWM_L_PIN, APP_TIM_PWM_L_AF);
	/* INIT BUTTON PINS */
	MGPIO_vSetPinMode(APP_BUTTON_APP1, MGPIO_MODE_INPUT);
	MGPIO_vSetPinInputType(APP_BUTTON_APP1, MGPIO_INPUT_TYPE_PULLUP);
	MGPIO_vSetPinMode(APP_BUTTON_APP2, MGPIO_MODE_INPUT);
	MGPIO_vSetPinInputType(APP_BUTTON_APP2, MGPIO_INPUT_TYPE_PULLUP);
	/* INIT DIRECTION PINS */
	MGPIO_vSetPinMode(APP_DIRECTION_R, MGPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(APP_DIRECTION_R, MGPIO_OUTPUT_TYPE_PP);
	MGPIO_vSetPinOutputSpeed(APP_DIRECTION_R, MGPIO_HIGH_SPEED);
	MGPIO_vSetPinMode(APP_DIRECTION_L, MGPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(APP_DIRECTION_L, MGPIO_OUTPUT_TYPE_PP);
	MGPIO_vSetPinOutputSpeed(APP_DIRECTION_L, MGPIO_HIGH_SPEED);
	MGPIO_vSetPinValue(APP_DIRECTION_R, MGPIO_OUTPUT_LOW);
	MGPIO_vSetPinValue(APP_DIRECTION_L, MGPIO_OUTPUT_LOW);
	/**********************************************************************************************/

	/************************************* ADC CONFIGURATIONS *************************************/
	/* INITIALIZE ADC */
	MADC_vInit();
	/* SET THE NUMBER OF CONVERSIONS TO THE NUMBER OF IRS IN THE ARRAY */
	MADC_vSetNumberOfConversions(MADC_REGULAR_GROUP, MADC_FIVE_CONVERSIONS);
	/* SET ALL OF THEIR SAMPLE TIMES */
	MADC_vSetSamplingTime(APP_IR0_CHANNEL, MADC_SAMPLING_CYCLES_3);
	MADC_vSetSamplingTime(APP_IR1_CHANNEL, MADC_SAMPLING_CYCLES_3);
	MADC_vSetSamplingTime(APP_IR2_CHANNEL, MADC_SAMPLING_CYCLES_3);
	MADC_vSetSamplingTime(APP_IR3_CHANNEL, MADC_SAMPLING_CYCLES_3);
	MADC_vSetSamplingTime(APP_IR4_CHANNEL, MADC_SAMPLING_CYCLES_3);
	/* SET THEIR SEQUENCE */
	MADC_vSetSequence(MADC_REGULAR_GROUP, APP_IR0_CHANNEL, MADC_SEQUENCE_1);
	MADC_vSetSequence(MADC_REGULAR_GROUP, APP_IR1_CHANNEL, MADC_SEQUENCE_2);
	MADC_vSetSequence(MADC_REGULAR_GROUP, APP_IR2_CHANNEL, MADC_SEQUENCE_3);
	MADC_vSetSequence(MADC_REGULAR_GROUP, APP_IR3_CHANNEL, MADC_SEQUENCE_4);
	MADC_vSetSequence(MADC_REGULAR_GROUP, APP_IR4_CHANNEL, MADC_SEQUENCE_5);
	/**********************************************************************************************/

	/********************************* DMA CONFIGURATIONS FOR ADC *********************************/
	volatile u32* DMAsrcAddr = MADC_u32SetRegularDMA(MADC_ENABLE);
	/* Enable DMA */
	MDMA_DirectInitType dma = {MDMA_DISABLE, MDMA_DIRECTION_PER_MEM, MDMA_ENABLE,
								MDMA_DISABLE, MDMA_ENABLE, MDMA_PRIORITY_VHIGH, MDMA_CHANNEL_0};
	MDMA_TransferStruct dmat = {(u32*)DMAsrcAddr, (u32*)APP_u16IRData, 5, MDMA_SIZE_HWORD};
	MDMA_vDirectInit(DMA2, MDMA_STREAM_0, &dma);
	MDMA_vStart(DMA2, MDMA_STREAM_0, &dmat);
	MADC_vEnable(MADC_ENABLE, MADC_DISABLE);
	/**********************************************************************************************/

	/*********************************** GPT PWM CONFIGURATIONS ***********************************/
	MGPT_PWMInitTypeDef gpt = {APP_CHANNEL_PWM_R, MGPT_PWM_MODE_1, APP_PWM_PERIOD,
						APP_PWM_PRESCALER, MGPT_ALLIGNMENT_EDGE_MODE, MGPT_DIRECTION_UP_COUNTER,
						MGPT_CHANNEL_OUTPUT_ACTIVE_HIGH};
	MGPT_vPWMInit(APP_TIM_PWM_R, &gpt);
	gpt.Channel = APP_CHANNEL_PWM_L;
	MGPT_vPWMInit(APP_TIM_PWM_L, &gpt);
	/* SET THE SPEED TO 0 */
	MGPT_vSetPWMDutyCycle(APP_TIM_PWM_R, APP_CHANNEL_PWM_R, APP_CAR_MOVE_ZERO_FORCE);
	MGPT_vSetPWMDutyCycle(APP_TIM_PWM_L, APP_CHANNEL_PWM_L, APP_CAR_MOVE_ZERO_FORCE);
	/**********************************************************************************************/
}

/**
 * @brief Drive the motors by setting their direction and speed.
 *
 * This function sets the direction and speed of the motors to achieve the desired movement.
 * It first sets the direction of the right and left wheels using the provided parameters,
 * then it sets the speed of each wheel using PWM signals.
 *
 * @param Right_Dir Direction of the right wheel.
 * @param Left_Dir Direction of the left wheel.
 * @note The direction can be forward, backward, or stop.
 * @note The speed of the wheels should be set before calling this function.
 */
void APP_vDriveMotors(APP_WHEEL_DIR Right_Dir, APP_WHEEL_DIR Left_Dir) {
	/* SET THE WHEELS DIRECTION */
	MGPIO_vSetPinValue(APP_DIRECTION_R, Right_Dir);
	MGPIO_vSetPinValue(APP_DIRECTION_L, Left_Dir);
	/* SET THE WHEELS SPEED */
	MGPT_vSetPWMDutyCycle(APP_TIM_PWM_R, APP_CHANNEL_PWM_R, (u32)APP_s32SpeedRight);
	MGPT_vSetPWMDutyCycle(APP_TIM_PWM_L, APP_CHANNEL_PWM_L, (u32)APP_s32SpeedLeft);
}

/**
 * @brief Calibrate the line following sensors.
 *
 * This function calibrates the line following sensors by determining the minimum and maximum
 * values for each sensor reading. It rotates the robot to gather multiple readings from each sensor,
 * then calculates the threshold values to be used for line detection.
 *
 * @param None
 * @return None
 */
void APP_vCalibrateLineFollowing(void) {
	u16 minVal[APP_IR_ARRAY_COUNT];
	u16 maxVal[APP_IR_ARRAY_COUNT];
	/* INITIALIZE THE MINIMUM AND MAXIMUM */
	u8 i = 0;
	u16 greatcounter = 0;
	for (i = 0; i < APP_IR_ARRAY_COUNT; i++) {
		minVal[i] = APP_u16IRData[i];
		maxVal[i] = APP_u16IRData[i];
	}
	/* SET THE MOTOR TO MAX SPEED TO ROTATE THE ROBOT  TO GET MULTIPLE VALUES */
    APP_s32SpeedRight = APP_AVERAGE_SPEED;
    APP_s32SpeedLeft = APP_AVERAGE_SPEED;
    APP_vDriveMotors(APP_CLOCK_WISE, APP_ANTI_CLOCK_WISE);
	/* START CALIBRATION PROCESS */
	for (greatcounter = 0; greatcounter < 3000; greatcounter++) {
		for (i = 0; i < APP_IR_ARRAY_COUNT; i++) {
			if (APP_u16IRData[i] > maxVal[i]) { maxVal[i] = APP_u16IRData[i]; }
			if (APP_u16IRData[i] < minVal[i]) { minVal[i] = APP_u16IRData[i]; }
		}
	}
	/* SET THE THRESHOLD */
	for (i = 0; i < APP_IR_ARRAY_COUNT; i++) { APP_u16IRThreshold[i] = (minVal[i] + maxVal[i]) / 2; }
}

/**
 * @brief Calibrate maze solving parameters.
 *
 * This function initializes USART communication, configures DMA for USART control buffer,
 * performs calibration for direction, and then configures DMA for USART direction buffer.
 *
 * @note Calibration for direction may involve allowing the mobile device to control the car or
 *       allowing the car itself to perform calibration.
 * @note After calibration, the function calibrates line following sensors.
 *
 * @param None
 * @return None
 */
void APP_vCalibrateMazeSolving(void) {
	/************************************ USART CONFIGURATIONS ************************************/
	/* Initialize USART */
	MUSART_InitTypeDef uart = {9600, MUSART_DATAWIDTH_8BIT,
							MUSART_STOP_ONE_BIT, MUSART_DISABLE,
							MUSART_PARITY_EVEN, MUSART_DIRECTION_TX_RX,
							MUSART_DISABLE, MUSART_OVER_SAMPLING_16};
	MUSART_ClockInitTypeDef uart_clock = {MUSART_DISABLE, 0, 0, 0};	/* Disable USART's Clock */
	MUSART_vInit(APP_MOBILE_USART, &uart, &uart_clock);
	MUSART_vEnable(APP_MOBILE_USART);
	MUSART_vRxIntStatus(APP_MOBILE_USART, MUSART_DISABLE);
	/**********************************************************************************************/

	/************************* DMA CONFIGURATION FOR USART CONTROL BUFFER *************************/
	MDMA_DirectInitType dma = {MDMA_DISABLE, MDMA_DIRECTION_PER_MEM, MDMA_ENABLE,
								MDMA_DISABLE, MDMA_ENABLE, MDMA_PRIORITY_HIGH, MDMA_CHANNEL_4};
	MDMA_TransferStruct dmat = {(u32*)MUSART_u32EnableRxDMA(APP_MOBILE_USART),
								(u32*)(&APP_u8Control), 1, MDMA_SIZE_BYTE};
	MDMA_vDirectInit(DMA2, MDMA_STREAM_5, &dma);
	MDMA_vStart(DMA2, MDMA_STREAM_5, &dmat);
	/**********************************************************************************************/

	/********************************** CALIBRATION FOR DIRECTION *********************************/
	// TODO -- ALLOW THE MOBILE TO FULLY CONTROL THE CAR SO IT CAN CALIBRATE

	/* ALLOW THE CAR IT SELF TO CALIBRATE */
	APP_vCalibrateLineFollowing();
	/**********************************************************************************************/

	/************************ DMA CONFIGURATION FOR USART DIRECTION BUFFER ************************/
	dmat.DstAddr = (u32*)APP_u8DirBuffer;
	dmat.Length = APP_MOBILE_MSG_LEN;
	MDMA_vStart(DMA2, MDMA_STREAM_5, &dmat);
	/**********************************************************************************************/
}

/**
 * @brief Return the car to point zero.
 *
 * This function rotates the car until it reaches the black line detected by the middle sensor.
 * Once the black line is detected, the car stops.
 *
 * @param None
 * @return None
 */
void APP_vReturnToPointZero(void) {
	/* ROTATE THE CAR */
	APP_s32SpeedRight = APP_AVERAGE_SPEED;
	APP_s32SpeedLeft = APP_AVERAGE_SPEED;
	APP_vDriveMotors(APP_CLOCK_WISE, APP_ANTI_CLOCK_WISE);
	/* KEEP ROTATING UNTILL REACHING THE BLACK LINE IN THE MIDDLE SENSOR */
	while (APP_u16IRData[2] > APP_u16IRThreshold[2]);
	/* STOP THE CAR */
	APP_s32SpeedRight = APP_CAR_MOVE_ZERO_FORCE;
	APP_s32SpeedLeft = APP_CAR_MOVE_ZERO_FORCE;
	APP_vDriveMotors(APP_CLOCK_WISE, APP_CLOCK_WISE);
}

/**
 * @brief Perform PID control for car movement.
 *
 * This function calculates the PID control value based on the error between the sensor readings.
 * It adjusts the speed of the left and right wheels accordingly to maintain the desired path.
 *
 * @param None
 * @return None
 */
void APP_vPIDcontrol(void) {
	// FIXME -- USAGE FAULT APPEARS DUE TO FLOATING POINT
	/* GET PID CONSTANTS */
	APP_f32Kp = 0.0006 * (1000.0 - APP_u16IRData[2]);
	APP_f32Kd = 10.0 * APP_f32Kp;
	APP_f32Ki = 0.0001;
	/* GET CURRENT ERROR */
	APP_s32Error = APP_u16IRData[1] - APP_u16IRData[3];
	/* GET PID VARIABLES */
	APP_s32P = APP_s32Error;
	APP_s32I += APP_s32Error;
	APP_s32D = APP_s32Error - APP_s32PrevError;
	/* SET THE PREVIOUS ERROR */
	APP_s32PrevError = APP_s32Error;
	/* CALCULATE PID VALUE */
	s32 APP_s32PID = (APP_f32Kp * APP_s32P) + (APP_f32Kd * APP_s32D) + (APP_f32Ki * APP_s32I);
	APP_s32SpeedLeft = APP_AVERAGE_SPEED + APP_s32PID;
	APP_s32SpeedRight = APP_AVERAGE_SPEED - APP_s32PID;
	if (APP_s32SpeedLeft > APP_CAR_MOVE_FULL_FORCE) 	  { APP_s32SpeedLeft  = APP_CAR_MOVE_FULL_FORCE; }
	else if (APP_s32SpeedLeft < APP_CAR_MOVE_ZERO_FORCE)  { APP_s32SpeedLeft  = APP_CAR_MOVE_ZERO_FORCE; }
	if (APP_s32SpeedRight > APP_CAR_MOVE_FULL_FORCE) 	  { APP_s32SpeedRight = APP_CAR_MOVE_FULL_FORCE; }
	else if (APP_s32SpeedRight < APP_CAR_MOVE_ZERO_FORCE) { APP_s32SpeedRight = APP_CAR_MOVE_ZERO_FORCE; }
	APP_vDriveMotors(APP_CLOCK_WISE, APP_CLOCK_WISE);
}
