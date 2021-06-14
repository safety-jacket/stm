/*********************************************************************************/
/* Author    : Ahmed Hassan                                                      */
/* Version   : V02                                                               */
/* Date      : Jan 19,   2021                                                    */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

#include "RCC_interface.h"

void GPIO_vidSetPinDirection (u8 Copy_u8Port, u8 Copy_u8Pin, u8 u8Copy_u8Mode) {

    switch (Copy_u8Port)
    {
    case GPIOA:

        /* PINS 0...7 (CRL) */
        if (Copy_u8Pin<=7) 
        {
            GPIOA_CRL &= ~ (0xF << (Copy_u8Pin * 4));
            GPIOA_CRL |= (u8Copy_u8Mode << (Copy_u8Pin*4));
        }

        /* PINS 8...15 (CRH) */
        else if (Copy_u8Pin<=15) 
        {
            Copy_u8Pin -= 8;
            GPIOA_CRH &= ~ (0xF << (Copy_u8Pin * 4));
            GPIOA_CRH |= (u8Copy_u8Mode << (Copy_u8Pin*4));
        }

        break;

    case GPIOB:

        /* PINS 0...7 (CRL) */
        if (Copy_u8Pin<=7) 
        {
            GPIOB_CRL &= ~ (0xF << (Copy_u8Pin * 4));
            GPIOB_CRL |= (u8Copy_u8Mode << (Copy_u8Pin*4));
        }

        /* PINS 8...15 (CRH) */
        else if (Copy_u8Pin<=15) 
        {
            Copy_u8Pin -= 8;
            GPIOB_CRH &= ~ (0xF << (Copy_u8Pin * 4));
            GPIOB_CRH |= (u8Copy_u8Mode << (Copy_u8Pin*4));
        }

        break;

    case GPIOC:

        /* PINS 0...7 (CRL) */
        if (Copy_u8Pin<=7) 
        {   
            GPIOC_CRL &= ~ (0xF << (Copy_u8Pin * 4));
            GPIOC_CRL |= (u8Copy_u8Mode << (Copy_u8Pin*4));
        }

        /* PINS 8...15 (CRH) */
        else if (Copy_u8Pin<=15) 
        {
            Copy_u8Pin -= 8;
            GPIOC_CRH &= ~ (0xF << (Copy_u8Pin * 4));
            GPIOC_CRH |= (u8Copy_u8Mode << (Copy_u8Pin*4));
        }

        break;
    
    default:
        break;
    }

}

void GPIO_vidSetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin, u8 u8Copy_u8Value) {
    switch (Copy_u8Port)
    {

    case GPIOA:
        switch (u8Copy_u8Value)
        {
            case    STD_HIGH :  GPIOA_BSRR = (1<<Copy_u8Pin);  break;
            case    STD_LOW  :  GPIOA_BRR  = (1<<Copy_u8Pin);  break;
            default          :                                 break;

        }
        break;

    case GPIOB:
        switch (u8Copy_u8Value)
        {
            case    STD_HIGH :  GPIOB_BSRR = (1<<Copy_u8Pin);  break;
            case    STD_LOW  :  GPIOB_BRR  = (1<<Copy_u8Pin);  break;
            default          :                                 break;
        }
        break;

    case GPIOC:
        switch (u8Copy_u8Value)
        {
            case    STD_HIGH :  GPIOC_BSRR = (1<<Copy_u8Pin);  break;
            case    STD_LOW  :  GPIOC_BRR  = (1<<Copy_u8Pin);  break;
            default          :                                 break;
        }
        break;
    
    default:
        break;
    }
}

u8   GPIO_u8GetPinDirection (u8 Copy_u8Port, u8 Copy_u8Pin) {
    u8 LOC_u8Result = 0;
    switch (Copy_u8Port)
    {
    case GPIOA:

        /* PINS 0...7 (CRL) */
        if (Copy_u8Pin<=7) 
        {
            LOC_u8Result = 0x0F & (GPIOA_CRL>>(Copy_u8Pin*4));
        }

        /* PINS 8...15 (CRH) */
        else if (Copy_u8Pin<=15) 
        {
            Copy_u8Pin -= 8;
            LOC_u8Result = 0x0F & (GPIOA_CRH>>(Copy_u8Pin*4));
        }

        break;

    case GPIOB:

        /* PINS 0...7 (CRL) */
        if (Copy_u8Pin<=7) 
        {
            LOC_u8Result = 0x0F & (GPIOB_CRL>>(Copy_u8Pin*4));
        }

        /* PINS 8...15 (CRH) */
        else if (Copy_u8Pin<=15) 
        {
            Copy_u8Pin -= 8;
            LOC_u8Result = 0x0F & (GPIOB_CRH>>(Copy_u8Pin*4));
        }

        break;

    case GPIOC:

        /* PINS 0...7 (CRL) */
        if (Copy_u8Pin<=7) 
        {
            LOC_u8Result = 0x0F & (GPIOC_CRL>>(Copy_u8Pin*4));
        }

        /* PINS 8...15 (CRH) */
        else if (Copy_u8Pin<=15) 
        {
            Copy_u8Pin -= 8;
            LOC_u8Result = 0x0F & (GPIOC_CRH>>(Copy_u8Pin*4));
        }

        break;
    
    default:
        break;
    }
    return LOC_u8Result;
}

u8   GPIO_u8GetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin) {

    u8 LOC_u8Result = 0;
    u8 LOC_u8Mode = GPIO_u8GetPinDirection(Copy_u8Port, Copy_u8Pin);
    u8 LOC_u8OutputPP = FALSE;
    /*check if mode is push pull output*/
    if (       (LOC_u8Mode == 0b0001) 
            || (LOC_u8Mode == 0b1001)
            || (LOC_u8Mode == 0b0010) 
            || (LOC_u8Mode == 0b1010)
            || (LOC_u8Mode == 0b0011) 
            || (LOC_u8Mode == 0b1011) ) {
        LOC_u8OutputPP = TRUE;
    }

    switch (Copy_u8Port)
    {

    case GPIOA:
        /*If mode is output push pull then read the state from ODR*/
        if (LOC_u8OutputPP == TRUE) {
            LOC_u8Result = GET_BIT (GPIOA_ODR, Copy_u8Pin);
        }
        else {
            LOC_u8Result = GET_BIT (GPIOA_IDR, Copy_u8Pin);
        }
        break;

    case GPIOB:
        /*If mode is output push pull then read the state from ODR*/
        if (LOC_u8OutputPP == TRUE) {
            LOC_u8Result = GET_BIT (GPIOB_ODR, Copy_u8Pin);
        }
        else {
            LOC_u8Result = GET_BIT (GPIOB_IDR, Copy_u8Pin);
        }
        break;

    case GPIOC:
        /*If mode is output push pull then read the state from ODR*/
        if (LOC_u8OutputPP == TRUE) {
            LOC_u8Result = GET_BIT (GPIOC_ODR, Copy_u8Pin);
        }
        else {
            LOC_u8Result = GET_BIT (GPIOC_IDR, Copy_u8Pin);
        }
        break;

    default:
        break;
    }

    return LOC_u8Result;
}

u16  GPIO_u16GetPortValue (u8 Copy_u8Port) {
    u16 LOC_u16Result = 0;
    for (u8 pinCounter = 0; pinCounter<16; pinCounter++) {
        LOC_u16Result = (LOC_u16Result<<1) | GPIO_u8GetPinValue(Copy_u8Port, pinCounter);
    }
    return LOC_u16Result;

}

void GPIO_vidSetPortDirection (u8 Copy_u8Port, u8  Copy_u8Mode) {

    switch (Copy_u8Port)
    {
    case GPIOA:
        GPIOA_CRL = 0x00000000;
        GPIOA_CRH = 0x00000000;
        for (u8 i=0; i<8; i++) {
            GPIOA_CRL |= Copy_u8Mode << i*4;
            GPIOA_CRH |= Copy_u8Mode << i*4;
        }
        break;
    
    case GPIOB:
        GPIOB_CRL = 0x00000000;
        GPIOB_CRH = 0x00000000;
        for (u8 i=0; i<8; i++) {
            GPIOB_CRL |= Copy_u8Mode << i*4;
            GPIOB_CRH |= Copy_u8Mode << i*4;
        }
        break;
    
    case GPIOC:
        GPIOC_CRL = 0x00000000;
        GPIOC_CRH = 0x00000000;
        for (u8 i=0; i<8; i++) {
            GPIOC_CRL |= Copy_u8Mode << i*4;
            GPIOC_CRH |= Copy_u8Mode << i*4;
        }
        break;
    
    default:
        break;
    }
}

void GPIO_vidSetPortValue (u8 Copy_u8Port, u16 Copy_u16Value) {

    switch (Copy_u8Port)
    {
    case GPIOA:
        GPIOA_ODR = Copy_u16Value;
        break;
    case GPIOB:
        GPIOB_ODR = Copy_u16Value;
        break;
    case GPIOC:
        GPIOC_ODR = Copy_u16Value;
        break;
    default:
        break;
    }

}
       
void GPIO_vidSetPortLowPinsDirection (u8 Copy_u8Port, u8  Copy_u8Mode) {
    switch (Copy_u8Port)
    {
    case GPIOA:
        GPIOA_CRL = 0x00000000;
        for (u8 i=0; i<8; i++) {
            GPIOA_CRL |= Copy_u8Mode << i*4;
        }
        break;
    
    case GPIOB:
        GPIOB_CRL = 0x00000000;
        for (u8 i=0; i<8; i++) {
            GPIOB_CRL |= Copy_u8Mode << i*4;
        }
        break;
    
    case GPIOC:
        GPIOC_CRL = 0x00000000;
        for (u8 i=0; i<8; i++) {
            GPIOC_CRL |= Copy_u8Mode << i*4;
        }
        break;
    
    default:
        break;
    }

}

void GPIO_vidSetPortHighPinsDirection (u8 Copy_u8Port, u8  Copy_u8Mode) {
    switch (Copy_u8Port)
    {
    case GPIOA:
        GPIOA_CRH = 0x00000000;
        for (u8 i=0; i<8; i++) {
            GPIOA_CRH |= Copy_u8Mode << i*4;
        }
        break;
    
    case GPIOB:
        GPIOB_CRH = 0x00000000;
        for (u8 i=0; i<8; i++) {
            GPIOA_CRH |= Copy_u8Mode << i*4;
        }
        break;
    
    case GPIOC:
        GPIOC_CRH = 0x00000000;
        for (u8 i=0; i<8; i++) {
            GPIOA_CRH |= Copy_u8Mode << i*4;
        }
        break;
    
    default:
        break;
    }

}

void GPIO_vidSetPortLowPinsValue (u8 Copy_u8Port, u8  Copy_u8Value) {
    switch (Copy_u8Port)
    {
    case GPIOA:
        GPIOA_ODR &= 0xFFFFFF00;
        GPIOA_ODR |= Copy_u8Value;
        break;
    case GPIOB:
        GPIOB_ODR &= 0xFFFFFF00;
        GPIOB_ODR |= Copy_u8Value;
        break;
    case GPIOC:
        GPIOC_ODR &= 0xFFFFFF00;
        GPIOC_ODR |= Copy_u8Value;
        break;
    default:
        break;
    }

}

void GPIO_vidSetPortHighPinsValue (u8 Copy_u8Port, u8  Copy_u8Value) {
    switch (Copy_u8Port)
    {
    case GPIOA:
        GPIOA_ODR &= 0xFFFF00FF;
        GPIOA_ODR |= (Copy_u8Value<<8);
        break;
    case GPIOB:
        GPIOB_ODR &= 0xFFFF00FF;
        GPIOB_ODR |= (Copy_u8Value<<8);
        break;
    case GPIOC:
        GPIOC_ODR &= 0xFFFF00FF;
        GPIOC_ODR |= (Copy_u8Value<<8);
        break;
    default:
        break;
    }

}

u8   GPIO_u8TogglePinValue (u8 Copy_u8Port, u8 Copy_u8Pin) {

    u8 LOC_u8State;
    LOC_u8State = GPIO_u8GetPinValue(Copy_u8Port, Copy_u8Pin);
    switch (LOC_u8State)
    {
    case STD_HIGH:
        LOC_u8State = STD_LOW;
        GPIO_vidSetPinValue(Copy_u8Port, Copy_u8Pin, LOC_u8State);
        break;
    case STD_LOW:
        LOC_u8State = STD_HIGH;
        GPIO_vidSetPinValue(Copy_u8Port, Copy_u8Pin, LOC_u8State);
        break;
    default:
        break;
    }
    return LOC_u8State;

}

void GPIO_vidLockPin (u8 Copy_u8Port, u8 Copy_u8Pin) {
    switch (Copy_u8Port)
    {

    case GPIOA:
        GPIOA_LCKR = 0x00010000 | (1<<Copy_u8Pin); /* write 1 */
        GPIOA_LCKR =              (1<<Copy_u8Pin); /* write 0 */
        GPIOA_LCKR = 0x00010000 | (1<<Copy_u8Pin); /* write 1 */
        (void) GPIOA_LCKR; /* read 0 */
        (void) GPIOA_LCKR; /* read 1 */
        break;

    case GPIOB:
        GPIOB_LCKR = 0x00010000 | (1<<Copy_u8Pin); /* write 1 */
        GPIOB_LCKR =              (1<<Copy_u8Pin); /* write 0 */
        GPIOB_LCKR = 0x00010000 | (1<<Copy_u8Pin); /* write 1 */
        (void) GPIOB_LCKR; /* read 0 */
        (void) GPIOB_LCKR; /* read 1 */
        break;

    case GPIOC:
        GPIOC_LCKR = 0x00010000 | (1<<Copy_u8Pin); /* write 1 */
        GPIOC_LCKR =              (1<<Copy_u8Pin); /* write 0 */
        GPIOC_LCKR = 0x00010000 | (1<<Copy_u8Pin); /* write 1 */
        (void) GPIOC_LCKR; /* read 0 */
        (void) GPIOC_LCKR; /* read 1 */
        break;
    
    default:
        break;
    }

}

void GPIO_vidEnablePortClock (u8 Copy_u8Port) {
    switch (Copy_u8Port)
    {
    case GPIOA:
        RCC_vidEnableClock(RCC_APB2 , IOPAEN);
        break;
    case GPIOB:
        RCC_vidEnableClock(RCC_APB2 , IOPBEN);
        break;
    case GPIOC:
        RCC_vidEnableClock(RCC_APB2 , IOPCEN);
        break;
    default:
        break;
    }
}
