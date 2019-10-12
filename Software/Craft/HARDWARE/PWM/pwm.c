#include "pwm.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//PWM  驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数


void TIM1_PWM_Init(u16 arr,u16 psc)//A8 A9 A10
{  
	 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

//  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	
//	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式，TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出比较极性低
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能定时器TIM2在CCR1上的预装载值
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能定时器TIM2在CCR2上的预装载值
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能定时器TIM2在CCR2上的预装载值
//	TIM_OC4Init(TIM1, &TIM_OCInitStructure);//根据结构体信息进行初始化
//	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能定时器TIM2在CCR2上的预装载值
	
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
 
   
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

////GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3 | GPIO_Remap_SWJ_JTAGDisable, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5   GPIO_FullRemap_TIM3   GPIO_PartialRemap_TIM3
////GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//关闭JTAG-DP，关闭SW-DP



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

