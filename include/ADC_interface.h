/*********************************************************************************/
/* Author    : Ahmed Hassan                                                      */
/* Version   : V01                                                               */
/* Date      : Jun 10,   2021                                                    */
/*********************************************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H


void ADC_vidInit(void);
u16 ADC_u16GetValue(u8 Copy_u8ChannelNumber);
void ADC_vidEnableClock(void);

#define ADC_CHANNEL0_PIN GPIOA, PIN0
#define ADC_CHANNEL1_PIN GPIOA, PIN1
#define ADC_CHANNEL2_PIN GPIOA, PIN2
#define ADC_CHANNEL3_PIN GPIOA, PIN3
#define ADC_CHANNEL4_PIN GPIOA, PIN4
#define ADC_CHANNEL5_PIN GPIOA, PIN5
#define ADC_CHANNEL6_PIN GPIOA, PIN6
#define ADC_CHANNEL7_PIN GPIOA, PIN7
#define ADC_CHANNEL8_PIN GPIOB, PIN0
#define ADC_CHANNEL9_PIN GPIOB, PIN1

#define ADC_CHANNEL0 0
#define ADC_CHANNEL1 1
#define ADC_CHANNEL2 2
#define ADC_CHANNEL3 3
#define ADC_CHANNEL4 4
#define ADC_CHANNEL5 5
#define ADC_CHANNEL6 6
#define ADC_CHANNEL7 7
#define ADC_CHANNEL8 8
#define ADC_CHANNEL9 9


#endif