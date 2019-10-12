#include "pwm.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//PWM  ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��


void TIM1_PWM_Init(u16 arr,u16 psc)//A8 A9 A10
{  
	 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

//  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	
//	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//ѡ��ʱ��ģʽ��TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//����Ƚϼ��Ե�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);//���ݽṹ����Ϣ���г�ʼ��
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ�ܶ�ʱ��TIM2��CCR1�ϵ�Ԥװ��ֵ
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);//���ݽṹ����Ϣ���г�ʼ��
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ�ܶ�ʱ��TIM2��CCR2�ϵ�Ԥװ��ֵ
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);//���ݽṹ����Ϣ���г�ʼ��
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ�ܶ�ʱ��TIM2��CCR2�ϵ�Ԥװ��ֵ
//	TIM_OC4Init(TIM1, &TIM_OCInitStructure);//���ݽṹ����Ϣ���г�ʼ��
//	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ�ܶ�ʱ��TIM2��CCR2�ϵ�Ԥװ��ֵ
	
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
 
   
}



void TIM2_PWM_Init(u16 arr,u16 psc)//A0 A1 A2 A3

{  

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	                                                                     	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM2_CH1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM2_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM2_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  

  TIM_CtrlPWMOutputs(TIM2,ENABLE);		

 
//	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  	 
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);   
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);   
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  


	TIM_ARRPreloadConfig(TIM2, ENABLE); 


	TIM_Cmd(TIM2, ENABLE);  

}



//void TIM3_PWM_Init(u16 arr,u16 psc)//B0 B1 A6 A7
//{
//GPIO_InitTypeDef GPIO_InitStructure;
//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//TIM_OCInitTypeDef  TIM_OCInitStructure;


//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// 
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);  

////GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3 | GPIO_Remap_SWJ_JTAGDisable, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5   GPIO_FullRemap_TIM3   GPIO_PartialRemap_TIM3
////GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//�ر�JTAG-DP���ر�SW-DP



//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM3_CH3
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_Init(GPIOB, &GPIO_InitStructure);	

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM3_CH4
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_Init(GPIOB, &GPIO_InitStructure); 


////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //TIM3_CH1
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_Init(GPIOB, &GPIO_InitStructure);

////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//TIM3_CH2
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_Init(GPIOB, &GPIO_InitStructure);

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM3_CH2
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_Init(GPIOA, &GPIO_InitStructure);

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//TIM3_CH1
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_Init(GPIOA, &GPIO_InitStructure);

//TIM_TimeBaseStructure.TIM_Period = arr;
//TIM_TimeBaseStructure.TIM_Prescaler =psc;
//TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
//TIM_OCInitStructure.TIM_Pulse = 0; 
//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
//TIM_OC1Init(TIM3, &TIM_OCInitStructure);  

//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
//TIM_OCInitStructure.TIM_Pulse = 0; 
//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
//TIM_OC2Init(TIM3, &TIM_OCInitStructure);  

//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
//TIM_OCInitStructure.TIM_Pulse = 0; 
//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
//TIM_OC3Init(TIM3, &TIM_OCInitStructure);  

//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
//TIM_OCInitStructure.TIM_Pulse = 0; 
//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
//TIM_OC4Init(TIM3, &TIM_OCInitStructure);  

//TIM_CtrlPWMOutputs(TIM3,ENABLE);		


//TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  	 
//TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);   
//TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);   
//TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  


//TIM_ARRPreloadConfig(TIM3, ENABLE); 


//TIM_Cmd(TIM3, ENABLE);
//}


//void TIM4_PWM_Init(u16 arr,u16 psc)//	B6 B7 B8 B9
//{  

//GPIO_InitTypeDef GPIO_InitStructure;
//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//TIM_OCInitTypeDef  TIM_OCInitStructure;

//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// 
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //


//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM4_CH1
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_Init(GPIOB, &GPIO_InitStructure);

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_Init(GPIOB, &GPIO_InitStructure);

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_Init(GPIOB, &GPIO_InitStructure);

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_Init(GPIOB, &GPIO_InitStructure);


//TIM_TimeBaseStructure.TIM_Period = arr; //
//TIM_TimeBaseStructure.TIM_Prescaler =psc; //
//TIM_TimeBaseStructure.TIM_ClockDivision = 0; //
//TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //
//TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //

//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //
//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //
//TIM_OCInitStructure.TIM_Pulse = 0; //
//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //
//TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //

//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //
//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //
//TIM_OCInitStructure.TIM_Pulse = 0; //
//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //
//TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //

//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //
//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //
//TIM_OCInitStructure.TIM_Pulse = 0; //
//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //
//TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //


//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //
//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //
//TIM_OCInitStructure.TIM_Pulse = 0; //
//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //
//TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //

//TIM_CtrlPWMOutputs(TIM4,ENABLE);	//

//TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //
//TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //
//TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //
//TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //

//TIM_ARRPreloadConfig(TIM4, ENABLE); //

//TIM_Cmd(TIM4, ENABLE);  //
//}

