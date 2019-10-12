#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY_UP  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//��ȡ����UP
#define KEY_DOWM  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)//��ȡ����DOWM
#define KEY_LEFT  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//��ȡ����LEFT 
#define KEY_RIGHT   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//��ȡ����RIGHT 
#define KEY_MID   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����MID 
 

#define KEY_UP_PRES 	1	//KEY0����
#define KEY_DOWM_PRES	2	//KEY1����
#define KEY_LEFT_PRES	3	//KEY2����
#define KEY_RIGHT_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)
#define KEY_MID_PRES   5	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
