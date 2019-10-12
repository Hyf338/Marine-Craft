#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
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
								    
//������ʼ������
extern u8 HW_value;
 
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC0.1.2.3
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
	
}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up &&(KEY_UP==0||KEY_DOWM==0||KEY_LEFT==0||KEY_RIGHT==0||KEY_MID==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY_UP==0)return KEY_UP_PRES;
		else if(KEY_DOWM==0)return KEY_DOWM_PRES;	
		else if(KEY_LEFT==0)return KEY_LEFT_PRES;	
		else if(KEY_RIGHT==0)return KEY_RIGHT_PRES;
		else if(KEY_MID==0)return KEY_MID_PRES;
		
	}else if(KEY_UP==1&&KEY_DOWM==1&&KEY_LEFT==1&&KEY_RIGHT==1&&KEY_MID==1)key_up=1; 	    //&&KEY2==1&&WK_UP==0
 	return 0;// �ް�������
}
