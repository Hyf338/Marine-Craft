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


#define KEY_UP  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//��ȡ����UP
#define KEY_DOWM  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����DOWM
#define KEY_confirm  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//��ȡ����DOWM
 

#define KEY_UP_PRES 	1	//KEYUP����
#define KEY_DOWM_PRES	2	//KEYDW����
#define KEY_DOWM_COMFIRM 3; //KEY RIGHTEST



void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
