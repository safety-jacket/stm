/*********************************************************************************/
/* Author    : Ahmed Hassan                                                      */
/* Version   : V01                                                               */
/* Date      : Jun 08,   2021                                                    */
/*********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "delay.h"

void ADC_vidInit(void)
{
	RCC_vidEnableClock(RCC_APB2, ADC1EN); /* Enable clock for ADC */
	SET_BIT((ADC1->CR2), 0);			  /* Enable ADC */
	delayMS(1);							  /* Wait two cycles */
	SET_BIT((ADC1->CR2), 2);			  /* Enable ADC */
	while (GET_BIT((ADC1->CR2), 2) == 1)
		; /* Wait fo calibration ends */
}

u16 ADC_u16GetValue(u8 Copy_u8ChannelNumber)
{
	ADC1->SQR1 = 0;						/* 1 conversion */
	ADC1->SQR3 = 0;						/* 1 conversion */
	ADC1->SQR3 |= Copy_u8ChannelNumber; /* first conversion */

	/* wirte sample time */
	if (Copy_u8ChannelNumber <= 9)
	{
		ADC1->SMPR2 |= ADC1_SAMPLE_TIME << (3 * Copy_u8ChannelNumber);
	}
	else if (Copy_u8ChannelNumber >= 10 && Copy_u8ChannelNumber <= 17)
	{
		ADC1->SMPR2 |= ADC1_SAMPLE_TIME << (3 * (Copy_u8ChannelNumber - 10));
	}

	SET_BIT(ADC1->CR2, 0); /* Start conversion */
	while ((ADC1->SR & (0x00000002)) == 0)
		; /* Wait conversion done */
	return ADC1->DR;
}

void ADC_vidEnableClock(void)
{
	RCC_vidEnableClock(RCC_APB2, ADC1EN);
}