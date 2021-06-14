
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "APP_interface.h"
#include "APP_private.h"
#include "APP_config.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "ADC_interface.h"
#include "USART_interface.h"
#include "NVIC_interface.h"
#include "delay.h"

volatile boolean g_bluetoothReceiveFlag = FALSE;
volatile u8 g_bluetoothReceiveValue;

void APP_vidInit(void)
{
    RCC_vidInitSysClock();          /* Init system clock */
    ADC_vidEnableClock();           /* Enable clock for ADC */
    GPIO_vidEnablePortClock(GPIOA); /* Enable clock for GPIOA */
    USART1_vidEnableClock();

    delayInit();      /* Init delay functions */
    ADC_vidInit();    /* Init ADC */
    USART1_vidInit(); /* Init USART1  */
    NVIC_vidInit();   /* Init NVIC  */

    GPIO_vidSetPinDirection(APP_BLUETOOTH_TX_PIN, OUTPUT_SPEED_50MHZ_AFPP); /* Bluetooth module Tx pin */
    GPIO_vidSetPinDirection(APP_BLUETOOTH_RX_PIN, INPUT_FLOATING);          /* Bluetooth module Rx pin */
    GPIO_vidSetPinDirection(APP_FLAME_PIN, INPUT_ANLOG);                    /* Flame sensor input pin */
    GPIO_vidSetPinDirection(APP_SMOKE_PIN, INPUT_ANLOG);                    /* Smoke sensor input pin */
    GPIO_vidSetPinDirection(APP_IR_PIN, INPUT_FLOATING);                    /* IR sensor input pin */

    NVIC_vidEnableInterrupt(NVIC_USART1);                      /* Enable interrupt for UART */
    USART1_vidEnableRecieveInterrupt(APP_vidReceiveBluetooth); /* Enable interrupt for UART and set callback */

    delayMS(50);
}

void APP_vidRun(void)
{
    u8 irState = APP_FALSE;
    u8 smokeState = APP_FALSE;
    u8 flameState = APP_FALSE;
    while (1)
    {
        u8 irValue = STD_HIGH;
        u16 smokeValue = 0;
        u16 flameValue = 0;
        flameValue = ADC_u16GetValue(APP_FLAME_CHANNEL);
        smokeValue = ADC_u16GetValue(APP_SMOKE_CHANNEL);
        irValue = GPIO_u8GetPinValue(APP_IR_PIN);
        if (g_bluetoothReceiveFlag == TRUE)
        {
            g_bluetoothReceiveFlag = FALSE;
            switch (g_bluetoothReceiveValue)
            {
            case APP_IR_ID:
                USART1_vidTransmit(irState);
                break;
            case APP_SMOKE_ID:
                USART1_vidTransmit(smokeState);
                break;
            case APP_FLAME_ID:
                USART1_vidTransmit(flameState);
                break;
            default:
                break;
            }
        }
        if (flameValue <= APP_FLAME_THRESHOLD)
        {
            flameState = APP_TRUE;
        }
        else
        {
            flameState = APP_FALSE;
        }

        if (smokeValue >= APP_SMOKE_THRESHOLD)
        {
            smokeState = APP_TRUE;
        }
        else
        {
            smokeState = APP_FALSE;
        }

        if (irValue == STD_LOW)
        {
            irState = APP_TRUE;
        }
        else
        {
            irState = APP_FALSE;
        }
    }
}

static void APP_vidReceiveBluetooth(u8 value)
{
    g_bluetoothReceiveValue = value;
    g_bluetoothReceiveFlag = TRUE;
}
