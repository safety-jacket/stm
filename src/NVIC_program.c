/*********************************************************************************/
/* Author    : Ahmed Hassan                                                      */
/* Version   : V01                                                               */
/* Date      : Jan 28,   2021                                                    */
/*********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

void NVIC_vidInit (void) {

    //TODO call function from SCB Driver to change SCB_AIRCR

    #define SCB_AIRCR *((volatile u32*)(0xE000ED0C))
    SCB_AIRCR = NVIC_GROUP_SUB_DISTRIBUTION;

}

void NVIC_vidEnableInterrupt (u8 copy_u8PeripheralIndex) {

    if (copy_u8PeripheralIndex<=31) {
        NVIC_ISER0 = (1<<copy_u8PeripheralIndex);
    }

    else if (copy_u8PeripheralIndex<=63) {
        copy_u8PeripheralIndex -= 32;
        NVIC_ISER1 = (1<<copy_u8PeripheralIndex);
    }
    
    else {
        /* Return Error*/
    }
}

void NVIC_vidDisableInterrupt (u8 copy_u8PeripheralIndex) {

    if (copy_u8PeripheralIndex<=31) {
        NVIC_ICER0 = (1<<copy_u8PeripheralIndex);
    }

    else if (copy_u8PeripheralIndex<=63) {
        copy_u8PeripheralIndex -= 32;
        NVIC_ICER1 = (1<<copy_u8PeripheralIndex);
    }

    else {
        /* Return Error*/
    }
}

void NVIC_vidSetPendingFlag (u8 copy_u8PeripheralIndex) {

    if (copy_u8PeripheralIndex<=31) {
        NVIC_ISPR0 = (1<<copy_u8PeripheralIndex);
    }

    else if (copy_u8PeripheralIndex<=63) {
        copy_u8PeripheralIndex -= 32;
        NVIC_ISPR1 = (1<<copy_u8PeripheralIndex);
    }

    else {
        /* Return Error*/
    }

}

void NVIC_vidClearPendingFlag (u8 copy_u8PeripheralIndex) {

    if (copy_u8PeripheralIndex<=31) {
        NVIC_ICPR0 = (1<<copy_u8PeripheralIndex);
    }

    else if (copy_u8PeripheralIndex<=63) {
        copy_u8PeripheralIndex -= 32;
        NVIC_ICPR1 = (1<<copy_u8PeripheralIndex);
    }

    else {
        /* Return Error*/
    }

}

void NVIC_vidSetPriority (u8 copy_u8PeripheralIndex, u8 copy_u8GroupPriority, u8 copy_u8SubPriority) {

    u8 local_u8Priority = 0;

    if (copy_u8PeripheralIndex < 60) {

        if      (NVIC_GROUP_SUB_DISTRIBUTION == NVIC_GROUP_4_SUB_0) {
            local_u8Priority = copy_u8GroupPriority << 4;
        }

        else if (NVIC_GROUP_SUB_DISTRIBUTION == NVIC_GROUP_0_SUB_4) {
            local_u8Priority = copy_u8SubPriority   << 4;
        }

        else if (NVIC_GROUP_SUB_DISTRIBUTION == NVIC_GROUP_3_SUB_1) {
            local_u8Priority = (copy_u8GroupPriority << 5) | (copy_u8SubPriority << 4);
        }

        else if (NVIC_GROUP_SUB_DISTRIBUTION == NVIC_GROUP_2_SUB_2) {
            local_u8Priority = (copy_u8GroupPriority << 6) | (copy_u8SubPriority << 4);
        }

        else if (NVIC_GROUP_SUB_DISTRIBUTION == NVIC_GROUP_1_SUB_3) {
            local_u8Priority = (copy_u8GroupPriority << 7) | (copy_u8SubPriority << 4);
        }

        NVIC_IPR[copy_u8PeripheralIndex] = local_u8Priority;
    }

    else {
        /* Return Error*/
    }


}

u8   NVIC_u8GetActiveFlag (u8 copy_u8PeripheralIndex) {

    u8 Local_u8Result = 0;

    if (copy_u8PeripheralIndex<=31) {
        Local_u8Result = GET_BIT(NVIC_IABR0, copy_u8PeripheralIndex);
    }

    else if (copy_u8PeripheralIndex<=63) {
        copy_u8PeripheralIndex -= 32;
        Local_u8Result = GET_BIT(NVIC_IABR1, copy_u8PeripheralIndex);
    }

    else {
        /* Return Error*/
    }

    return Local_u8Result;

}
