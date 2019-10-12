#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#include "stm32f10x_tim.h"


void TIM1_Int_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);

#endif
