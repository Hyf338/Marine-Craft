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
				OLED_DrawPoint(108-0.5*x,x,1);//��б�� б�ʡ֡�3/3
				OLED_DrawPoint(17 +0.5*x,x,1);
				y = 30-x;
				OLED_DrawPoint(64-0.5*y,y,1);
				OLED_DrawPoint(64+0.5*y,y,1);
			  OLED_Refresh_Gram();//������ʾ��OLED
		}

	OLED_Refresh_Gram();
}


 int main(void)
 {	
  KEY_Init(); //IO��ʼ��
	delay_init();	    	 //��ʱ������ʼ��	 
	OLED_Init();//OLED��ʼ��
  uart2_init(115200);
//  Boot_Animation();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	TIM3_PWM_Init(499,71);	 //72��Ƶ��500��װ��ֵ  f=2k Hz   ���
	TIM2_PWM_Init(20000 ,71); //72��Ƶ��20000��װ��ֵ   f= 50 Hz�� ���
	TIM4_Int_Init(50000,35);//144��Ƶ��50000��װ��ֵ   f= 10Hz��T=100ms��������ռ������Ϊ108ms���ɼ�ʱ��
	TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE ); //�رն�ʱ��TIM4�жϣ�
	
	
//	OLED_ShowString(10, 5,(u8 *)"2019.3.17",12);
//	OLED_ShowString(10,15,(u8 *)"Motor1:",12);
//	OLED_ShowString(10,25,(u8 *)"Servo:",12);
//	OLED_ShowString(10,35,(u8 *)"infrared:",12);
//	OLED_ShowString(10,45,(u8 *)"servo_PWM:",12);
//	OLED_Refresh_Gram();
	infrared_Init();
	TIM_SetCompare2(TIM2,1210);	//���
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
			TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
//			infrared_receive_1();
			infrared_receive_1();
			TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE ); //�رն�ʱ��TIM4�жϣ�
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
				
		
		TIM_SetCompare2(TIM2,servo);	//���
		TIM_SetCompare2(TIM3,Motor2);		   
		TIM_SetCompare1(TIM3,Motor1);	 
		page();
	}	 	
 }

