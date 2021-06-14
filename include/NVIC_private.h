/*********************************************************************************/
/* Author    : Ahmed Hassan                                                      */
/* Version   : V01                                                               */
/* Date      : Jan 28,   2021                                                    */
/*********************************************************************************/

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

#define NVIC_ISER0           *((volatile u32*)(0xE000E100))
#define NVIC_ISER1           *((volatile u32*)(0xE000E104))
#define NVIC_ICER0           *((volatile u32*)(0xE000E180))
#define NVIC_ICER1           *((volatile u32*)(0xE000E184))
#define NVIC_ISPR0           *((volatile u32*)(0xE000E200))
#define NVIC_ISPR1           *((volatile u32*)(0xE000E204))
#define NVIC_ICPR0           *((volatile u32*)(0xE000E280))
#define NVIC_ICPR1           *((volatile u32*)(0xE000E284))
#define NVIC_IABR0           *((volatile u32*)(0xE000E300))
#define NVIC_IABR1           *((volatile u32*)(0xE000E304))
#define NVIC_IPR              ((volatile u8* )(0xE000E400))

#define NVIC_GROUP_4_SUB_0   0x05FA0300
#define NVIC_GROUP_3_SUB_1   0x05FA0400
#define NVIC_GROUP_2_SUB_2   0x05FA0500
#define NVIC_GROUP_1_SUB_3   0x05FA0600
#define NVIC_GROUP_0_SUB_4   0x05FA0700

#endif