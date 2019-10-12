#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//SSD1306 OLED ����IC��������
//������ʽ:8080����/4�ߴ���
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


//OLEDģʽ����
//0: 4�ߴ���ģʽ  ��ģ���BS1��BS2����GND��
//1: ����8080ģʽ ��ģ���BS1��BS2����VCC��
#define OLED_MODE 	0 
		    						  
//---------------------------OLED�˿ڶ���--------------------------  		
//RES=RST=B7
//RS=DC=B6
//ʱ��D0=B9
//����D1=B8
//-------------------------------------------------------

#define OLED_CS  PBout(10)		//�ӵ�
#define OLED_RST PBout(7) 		//RES=RST=B7
#define OLED_RS  PBout(6)			//RS=DC=B6
#define OLED_WR  PGout(14)		//???
#define OLED_RD  PGout(13)	   //???
//PC0~7,��Ϊ������
 
#define DATAOUT(x) GPIO_Write(GPIOC,x);//���  ???
  
//ʹ��4�ߴ��нӿ�ʱʹ�� 
#define OLED_SCLK PBout(9)	//ʱ��D0=B9
#define OLED_SDIN PBout(8)	//����D1=B8
		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);  		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);	 
void Boot_Animation(void);
void draw_circle(u8 x0,u8 y0,u8 r) ;
#endif  
	 







 

