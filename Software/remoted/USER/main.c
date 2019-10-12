#include "stm32f10x.h"

#include "mpuiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

#include "delay.h"
#include "oled.h"
#include "usart.h"
#include "timer.h"
#include "control.h"
#include "key.h"
#include "adc.h"
#include "display.h"

/****************************************************************
Ӳ������:

Zigbee(uart1):			ESP8266(uart2):				NRF24L01:
TX -> PA9						TX -> PA2							NRF_CE -> PA0
RX -> PA10					RX -> PA3							NRF_CS -> PA1
																					NRF_IRQ -> PA4
																					SPI1_CLK -> PA5
																					SPI1_MISO -> PA6
																					SPI1_MOSI -> PA7
												
ָʾ��:							������:								OLED:
State -> PB12				BUZZ -> PB4						D0 -> PB9
Heart -> PB13															D1 -> PB8
																					RES -> PB7
																					DC -> PB6
																					
����:								ҡ��:										
PaUp -> PC4         Throttle -> PC2					
PaDn -> PC5         Yaw -> PC3							
RowUp -> PB1        Pitch -> PC1
RowDn -> PB0        Roll -> PC0
enter -> PC9
MODE -> PC8
C1 -> PB14
C2 -> PB15
C3 -> PC6
C4 -> PC7


MPU6050:
IMUSCL -> PB10
IMUSDA -> PB11
****************************************************************/

float pitch,roll,yaw; 		//ŷ����									//������		������		�����
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	//������ԭʼ����
short temp;					//�¶�
char AD1=0,AD2=0,AD3=0,AD4=0;
short AD1_get=0,AD2_get=0,AD3_get=0,AD4_get=0;

extern signed short int Pitch,Roll,Yaw;
extern u8 send_data;

typedef enum
{
	sunday,  //0
	monday,
	thuesday,
	wednesday = 5,
	tuesday,
	friday,
	saturday
}WeekType;

WeekType week;

 int main(void)
 {
	 
	 delay_init();	    	//��ʱ������ʼ��
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	
	
	 OLED_Init();
	 BUZZ_Init();
//	 uart_init(115200);//zigbee����ͨ��
	 KEY_Init(); //IO��ʼ��
	 Adc_Init();

	 
	 MPU_Init();					//��ʼ��MPU6050
	 
	 while(mpu_dmp_init())
   {
		OLED_ShowString1(0,3,"Error");
		delay_ms(200);
   }
	 
   TIM4_Int_Init(50000,107);
	 TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx
		OLED_Clear();
   while(1)
	 {		 
		 AD1_get=Get_Adc_Average(ADC_Channel_10,10);
		 AD2_get=Get_Adc_Average(ADC_Channel_11,10);
		 AD3_get=Get_Adc_Average(ADC_Channel_12,10);
		 AD4_get=Get_Adc_Average(ADC_Channel_13,10);
		 
		 AD2=100*AD2_get/4096;
		 AD3=100*(4096-AD3_get)/4096;
		 
		 Page2();
	 }
 }

