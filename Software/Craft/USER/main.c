#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "key.h"
#include "oled.h"
#include "control.h"
#include "usart.h"



int Motor1=150;
int Motor2=0;
u8 key_v=0,mode=0;
u8 receive_motor=0,receive_servo=0;
int servo=1210;
extern int Expect_servo;
extern int servo_PWM;
extern u8 infrared;
extern void infrared_Init(void);
extern u8 infrared_bit_move(void);
extern void infrared_receive(void);
extern void TIM4_Int_Init(u16 arr,u16 psc);
extern void servo_PD(void);
extern void infrared_receive_1(void);
extern void infrared_receive_2(void);


void page()
{
			static u8 x=0,y=0;
	draw_circle(35,30,30);
		for(x = 70;x>=30;x--)
		{
				OLED_DrawPoint(108-0.5*x,x,1);//画斜线 斜率≈√3/3
				OLED_DrawPoint(17 +0.5*x,x,1);
				y = 30-x;
				OLED_DrawPoint(64-0.5*y,y,1);
				OLED_DrawPoint(64+0.5*y,y,1);
			  OLED_Refresh_Gram();//更新显示到OLED
		}

	OLED_Refresh_Gram();
}


 int main(void)
 {	
  KEY_Init(); //IO初始化
	delay_init();	    	 //延时函数初始化	 
	OLED_Init();//OLED初始化
  uart2_init(115200);
//  Boot_Animation();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	TIM3_PWM_Init(499,71);	 //72分频，500重装载值  f=2k Hz   电机
	TIM2_PWM_Init(20000 ,71); //72分频，20000重装载值   f= 50 Hz； 舵机
	TIM4_Int_Init(50000,35);//144分频，50000重装载值   f= 10Hz，T=100ms；红外接收检测周期为108ms；采集时间
	TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE ); //关闭定时器TIM4中断，
	
	
//	OLED_ShowString(10, 5,(u8 *)"2019.3.17",12);
//	OLED_ShowString(10,15,(u8 *)"Motor1:",12);
//	OLED_ShowString(10,25,(u8 *)"Servo:",12);
//	OLED_ShowString(10,35,(u8 *)"infrared:",12);
//	OLED_ShowString(10,45,(u8 *)"servo_PWM:",12);
//	OLED_Refresh_Gram();
	infrared_Init();
	TIM_SetCompare2(TIM2,1210);	//舵机
	delay_ms(10);
	 
  while(1)
	{
 	
		
		key_v=KEY_Scan(0);
	
		if(key_v==KEY_UP_PRES) Motor1+=10;
		if(key_v==KEY_DOWM_PRES) Motor1-=10;
		
//		OLED_ShowNum(75,15,Motor1,3,12);
//		OLED_ShowNum(85,35,infrared,3,12);
//		OLED_ShowNum(85,45,servo,4,12);
		if(mode==0)
		{
			Motor1=150;
			TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
//			infrared_receive_1();
			infrared_receive_1();
			TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE ); //关闭定时器TIM4中断，
			servo=Expect_servo;
			if(infrared==0xff)  Motor1=0; 
				else Motor1=150;
		}
		if(mode==1)
		{
			Motor1=2*receive_motor;
			servo=1210+5*(50-receive_servo);
		}
		
	 servo= (servo>1600)? 1600:servo;
	 servo= (servo<850)? 850:servo;
				
		
		TIM_SetCompare2(TIM2,servo);	//舵机
		TIM_SetCompare2(TIM3,Motor2);		   
		TIM_SetCompare1(TIM3,Motor1);	 
		page();
	}	 	
 }

