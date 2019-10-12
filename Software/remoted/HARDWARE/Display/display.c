#include "display.h"
#include "oled.h"
#include "usart.h"
u8 mode=0;
extern int Motor1,Motor2;
extern u8 Pitch,Roll,Yaw;
extern u8 send_data[8];
extern short AD1,AD2,AD3,AD4;

void Page1(void)
{
//	OLED_Clear();
	OLED_ShowCHinese1(27,0,0);
	OLED_ShowCHinese1(45,0,1);
	OLED_ShowCHinese1(63,0,2);
	OLED_ShowCHinese1(81,0,3);
	OLED_ShowString1(0,2,"Pitch");
	OLED_ShowString1(0,4,"Roll");
	OLED_ShowString1(0,6,"Yaw");  
	Dis_Float(2,71,Pitch,2);
	Dis_Float(4,71,Roll,2);
	Dis_Float(6,71,Yaw,2);	
	if(send_data[7]==0x01)
	{
		OLED_ShowString1(110,6,"*");
	}
}

void Page2(void)
{
	//OLED_Clear();
	OLED_ShowCHinese1(27,0,4);
	OLED_ShowCHinese1(45,0,5);
	OLED_ShowCHinese1(63,0,6);
	OLED_ShowCHinese1(81,0,7);
	OLED_ShowString1(0,2,"AD2/S:");
	OLED_ShowString1(0,4,"AD3/M:");
	OLED_ShowString1(0,6,"mode:");
	Dis_Float(2,71,AD2,2);
	Dis_Float(4,71,AD3,2);
	if(send_data[4]==0x01)
	{
		mode=1;
		OLED_ShowString1(60,6,"remote");
	}	
	if(send_data[4]==0x00)
	{
		mode=0;
		OLED_ShowString1(60,6,"infrared");
	}
}
