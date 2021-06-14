
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "delay.h"

#include "HC06_interfave.h"
#include "HC06_private.h"
#include "HC06_config.h"
#include "USART_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"

void HC06_vidInit(void)
{
#if (HC06_USART_CHANNEL == HC06_USART1_MAIN)
    /* Init UART */
    USART1_vidInit();
    /* Set direction of UART Pins */
    GPIO_vidSetPinDirection(GPIOA, PIN9, OUTPUT_SPEED_50MHZ_AFPP); /* A09 - Tx */
    GPIO_vidSetPinDirection(GPIOA, PIN10, INPUT_FLOATING);         /* A10 - Rx */
    /* Enable interrupt for UART */
    NVIC_vidEnableInterrupt(NVIC_USART1);
    USART1_vidEnableRecieveInterrupt(HC05_vidCharReceived);
#endif
}

void HC06_vidReceive(void) {

}

static void HC05_vidCharReceived(u8 value)
{


        /* Init UART */
    USART1_vidInit();
    /* Set direction of UART Pins */
    GPIO_vidSetPinDirection(GPIOA, PIN9, OUTPUT_SPEED_50MHZ_AFPP); /* A09 - Tx */
    GPIO_vidSetPinDirection(GPIOA, PIN10, INPUT_FLOATING);         /* A10 - Rx */
    /* Enable interrupt for UART */
    NVIC_vidEnableInterrupt(NVIC_USART1);
    USART1_vidEnableRecieveInterrupt(HC06_vidReceive);

    GPIO_vidSetPinDirection(GPIOA, PIN0, OUTPUT_SPEED_2MHZ_PP);
    delayMS(1000);
    GPIO_vidSetPinValue(GPIOA, PIN0, STD_LOW);

    while (1)
    {
        GPIO_vidSetPinValue(GPIOA, PIN0, STD_HIGH);
        USART1_vidTransmit('A');
        USART1_vidTransmit('T');
        /*USART1_vidTransmit('+');
        USART1_vidTransmit('A');
        USART1_vidTransmit('D');
        USART1_vidTransmit('D');
        USART1_vidTransmit('R');
        USART1_vidTransmit('?');*/
        delayMS(2000);
    }

}