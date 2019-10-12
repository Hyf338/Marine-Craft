#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY_UP  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//读取按键UP
#define KEY_DOWM  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)//读取按键DOWM
#define KEY_LEFT  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//读取按键LEFT 
#define KEY_RIGHT   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//读取按键RIGHT 
#define KEY_MID   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键MID 
 

#define KEY_UP_PRES 	1	//KEY0按下
#define KEY_DOWM_PRES	2	//KEY1按下
#define KEY_LEFT_PRES	3	//KEY2按下
#define KEY_RIGHT_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)
#define KEY_MID_PRES   5	//KEY_UP按下(即WK_UP/KEY_UP)


void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
