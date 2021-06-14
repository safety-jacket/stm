/*********************************************************************************/
/* Author    : Ahmed Hassan                                                      */
/* Version   : V01                                                               */
/* Date      : Jan 30,   2021                                                    */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"


static void(*STK_callBack)(void);

static u8 STK_u8ModeOfInterval;

void STK_vidInit (void) {

	#if STK_CLK_SRC == STK_SRC_AHB
		/* Disable STK - Disable STK Interrupt - Set clock source AHB */
		STK_CTRL = 0x00000004;
		
	#else
		/* Disable STK - Disable STK Interrupt - Set clock source AHB/8 */
		STK_CTRL = 0;
		
	#endif
}

void STK_vidSetBusyWait ( u32 copy_u32Ticks ) {

	/* Load ticks to load register */
	STK_LOAD = copy_u32Ticks;
	
	/* Start Timer */
	SET_BIT(STK_CTRL, 0);
	
	/* Wait till flag is raised */
	while( (GET_BIT(STK_CTRL,16)) == 0);
	
	/* Stop Timer */
	CLR_BIT(STK_CTRL, 0);
	STK_LOAD = 0;
	STK_VAL  = 0;
	
}

void STK_vidSetIntervalSingle ( u32 copy_u32Ticks, void (*copy_ptr)(void) ) {
	/* Load ticks to load register */
	STK_LOAD = copy_u32Ticks;
	
	/* Start Timer */
	SET_BIT(STK_CTRL, 0);
	
	/* Save CallBack */
	STK_callBack = copy_ptr;
	
	/* Set Mode to Single */
	STK_u8ModeOfInterval = STK_SINGLE_INTERVAL;
	
	/* Enable STK Interrupt */
	SET_BIT(STK_CTRL, 1);
}

void STK_vidSetIntervalPeriodic ( u32 copy_u32Ticks, void (*copy_ptr)(void) ) {
	/* Load ticks to load register */
	STK_LOAD = copy_u32Ticks;
	
	/* Start Timer */
	SET_BIT(STK_CTRL, 0);
	
	/* Save CallBack */
	STK_callBack = copy_ptr;
	
	/* Set Mode to Single */
	STK_u8ModeOfInterval = STK_PERIOD_INTERVAL;
	
	/* Enable STK Interrupt */
	SET_BIT(STK_CTRL, 1);
}

void STK_vidStopInterval (void) {
	/* Disable STK Interrupt */
	CLR_BIT(STK_CTRL, 1);
	
	/* Stop Timer */
	CLR_BIT(STK_CTRL, 0);
	STK_LOAD = 0;
	STK_VAL  = 0;
}

u32  STK_u32GetElapsedTime (void) {
	u32 local_u32ElapsedTime;
	
	local_u32ElapsedTime = STK_LOAD - STK_VAL ;
	
	return local_u32ElapsedTime;
}

u32  STK_u32GetRemainingTime (void) {
	u32 local_u32RemainTime;
	
	local_u32RemainTime = STK_VAL;
	
	return local_u32RemainTime;
}

void SysTick_Handler (void) {
	
	if (STK_u8ModeOfInterval == STK_SINGLE_INTERVAL) {
		STK_vidStopInterval();
	}
	
	/* Callback notification */
	STK_callBack();
	
	/* Clear interrupt flag */
	(void) GET_BIT(STK_CTRL,16);
}
