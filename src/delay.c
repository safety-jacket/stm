/*********************************************************************************/
/* Author    : Ahmed Hassan                                                      */
/* Version   : V01                                                               */
/* Date      : Jan 20,   2021                                                    */
/*********************************************************************************/

#include "STD_TYPES.h"

#include "delay.h"
#include "RCC_interface.h"

u16 iterationsPerMilliSeconds = 50;


void delayInit (void) {
    u32 clockFrequency = RCC_u32GetClockFrequency(RCC_SYSCLK);
    iterationsPerMilliSeconds = clockFrequency/((NUMBER_OF_INSTRUCTONS_PER_ITERATION*1000));

}

void delayMS (u32 milliSeconds)
{
    volatile u64 count = milliSeconds*iterationsPerMilliSeconds;
    while(count--  > 1 );
}
