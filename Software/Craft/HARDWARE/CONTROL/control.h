#ifndef __TIMER_H
#define __TIMER_H
#include "control.h"
#include "sys.h"





void infrared_Init(void);
u8 infrared_bit_move(void);
void infrared_receive_1(void);
void infrared_receive_2(void);
char filter(void);
void servo_PD(void);


#endif

