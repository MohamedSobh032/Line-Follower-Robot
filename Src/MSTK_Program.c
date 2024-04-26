/******************************************************/
/* SWC: STK Driver                                    */
/* Author: Mohamed Sobh                               */
/* Version: v2.0                                      */
/* Date: 02 APR 2024                                  */
/* Description: This is the implem. of STK            */
/******************************************************/

#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"
#include "MSTK_Config.h"
#include "MSTK_Interface.h"
#include "MSTK_Private.h"

/* Global Pointer to Function */
void (*MSTK_CallBack)(void) = NULL;
/* Global Variable for Interval Mode */
u8 Global_u8CallMode = 0;

/****************************************/
/* Func. Name: MSTK_vInit               */
/* i/p arguments: nothing               */
/* o/p arguments: nothing               */
/* Desc. : This API Initializes SysTick */
/****************************************/
void MSTK_vInit(void) {
    /* Disable Systick */
    CLR_BIT(STK_CTRL, MSTK_CTRL_ENABLE_BIT);
    /* Disable Systick INT */
    CLR_BIT(STK_CTRL, MSTK_CTRL_TICKINT_BIT);
    /* Select SysTick CLK Source */
    WRITE_BITS(STK_CTRL, MSTK_CLOCK_SOURCE, ONE_BIT, MSTK_CTRL_CLKSOURCE_BIT);
}

/*************************************/
/* Func. Name: MSTK_vDisable         */
/* i/p arguments: nothing            */
/* o/p arguments: nothing            */
/* Desc. : This API Disables Systick */
/*************************************/
void MSTK_vDisable(void) {
    /* Disable Systick */
    CLR_BIT(STK_CTRL, MSTK_CTRL_ENABLE_BIT);
    /* Disable Systick INT */
    CLR_BIT(STK_CTRL, MSTK_CTRL_TICKINT_BIT);
}

/***************************************************/
/* Func. Name: MSTK_vDelay                         */
/* i/p arguments: Copy_u32Ticks                    */
/* o/p arguments: nothing                          */
/* Desc. : This API Make Delay Using SysTick Timer */
/***************************************************/
void MSTK_vBusyWait(u32 Copy_u32Ticks) {
    /* Reload the value in the load register */
    STK_LOAD = Copy_u32Ticks;
    /* Start Systick */
    SET_BIT(STK_CTRL, MSTK_CTRL_ENABLE_BIT);
    /* Booling Till the Flag is Raised */
    while(!GET_BIT(STK_CTRL, MSTK_CTRL_COUNTFLAG_BIT));
    /* Stop the Timer */
    CLR_BIT(STK_CTRL, MSTK_CTRL_ENABLE_BIT);
    STK_LOAD = 0;
    STK_VAL = 0;
}

/******************************************************************************/
/* Func. Name: MSTK_vSingleCall                                               */
/* i/p arguments: Copy_u32Ticks                                               */
/* i/p arguments: LpF                                                         */
/* o/p arguments: nothing                                                     */
/* Desc. : This API allows to call a function for a single time using SysTick */
/******************************************************************************/
void MSTK_vSingleCall(u32 Copy_u32Ticks, void (*LpF)(void)) {
    /* Restart Timer */
    STK_LOAD = 0;
    STK_VAL = 0;
    /* Reload the value in the load register */
    STK_LOAD = Copy_u32Ticks;
    /* Start Timer */
    SET_BIT(STK_CTRL, MSTK_CTRL_ENABLE_BIT);
    /* Save Callback */
    MSTK_CallBack = LpF;
    /* Set Mode of Interval */
    Global_u8CallMode = MSTK_SINGLE_CALL_MODE;
    /* Enable SysTick INT */
    SET_BIT(STK_CTRL, MSTK_CTRL_TICKINT_BIT);
}

/*********************************************************************************/
/* Func. Name: MSTK_vPeriodicCall                                                */
/* i/p arguments: u32 Copy_u32Ticks                                              */
/* i/p arguments: LpF                                                            */
/* o/p arguments: nothing                                                        */
/* Desc. : This API allows to keep calling a function periodically using SysTick */
/*********************************************************************************/
void MSTK_vPeriodicCall(u32 Copy_u32Ticks, void (*LpF)(void)) {
    /* Restart Timer */
    STK_LOAD = 0;
    STK_VAL = 0;
    /* Reload the value in the load register */
    STK_LOAD = Copy_u32Ticks;
    /* Start Timer */
    SET_BIT(STK_CTRL, MSTK_CTRL_ENABLE_BIT);
    /* Save Callback */
    MSTK_CallBack = LpF;
    /* Set Mode of Interval */
    Global_u8CallMode = MSTK_PERIODIC_CALL_MODE;
    /* Enable SysTick INT */
    SET_BIT(STK_CTRL, MSTK_CTRL_TICKINT_BIT);
}

/********************************************/
/* Func. Name: MSTK_u32GetElapsedTicks      */
/* i/p arguments: Nothing                   */
/* o/p arguments: STK_LOAD - STK_VAL        */
/* Desc. : This API Return the Elapsed Time */
/********************************************/
u32 MSTK_u32GetElapsedTicks(void) { return (STK_LOAD - STK_VAL); }

/**********************************************/
/* Func. Name: MSTK_u32GetRemainingTicks      */
/* i/p arguments: nothing                     */
/* o/p arguments: STK_VAL                     */
/* Desc. : This API Return the Remaining Time */
/**********************************************/
u32 MSTK_u32GetRemainingTicks(void) { return STK_VAL; }

/*****************************************/
/* Func. Name: SysTick_Handler           */
/* i/p arguments: nothing                */
/* o/p arguments: nothing                */
/* Desc. : This API is SysTick Interrupt */
/*****************************************/
void SysTick_Handler() {
    if (Global_u8CallMode == MSTK_SINGLE_CALL_MODE) {
        /* Disable INT */
        CLR_BIT(STK_CTRL,MSTK_CTRL_TICKINT_BIT);
        /* Stop the Timer */
        CLR_BIT(STK_CTRL,MSTK_CTRL_ENABLE_BIT);
        STK_LOAD = 0;
        STK_VAL = 0;
    }
    if (MSTK_CallBack != NULL) { MSTK_CallBack(); }
    /* Clear Flag */
    (void)GET_BIT(STK_CTRL,MSTK_CTRL_COUNTFLAG_BIT);
}
