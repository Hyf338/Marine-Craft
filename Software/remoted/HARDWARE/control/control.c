#include "control.h"
#include "sys.h"

#include "mpuiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "usart.h"
#include "oled.h"

/*
	pitch    short     						ԭʼ����
	Pitch    signed short int     ǿ��ת�����з���16λ
	pitch_L  short int        		�Ͱ�λ
*/

u8 send_data[8]={0,0,0,0,0,0,0,0};
signed short int test_1=0;
int test_size=0;
signed short int pitch_L=0,pitch_H=0,roll_L=0,roll_H=0,yaw_L=0,yaw_H=0;
signed short int Pitch=0,Roll=0,Yaw=0;


extern float pitch,roll,yaw; 		//ŷ����									//������		������		�����
extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;	//������ԭʼ����
extern short temp;					//�¶�
extern short AD1,AD2,AD3,AD4;

void BUZZ_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);						 //PA.8 �����
}
 


void angle_get()
{
	if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
	{ 
		temp=MPU_Get_Temperature();	//�õ��¶�ֵ
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
	}
}



void data_process()
{
	u8 i=0;
	
	Pitch=(signed short int)pitch;
	Roll=(signed short int)roll;
	Yaw=(signed short int)yaw;
	
	send_data[i++]=0xaa;
	
	pitch_L=Pitch&0x00ff;
	send_data[i++]=pitch_L;
	pitch_H=Pitch&0xff00;
	pitch_H>>=8;
	send_data[i++]=pitch_H;
	
	roll_L=Roll&0x00ff;
	send_data[i++]=roll_L;
	roll_H=Roll&0xff00;
	roll_H>>=8;
	send_data[i++]=roll_H;
	
	yaw_L=Yaw&0x00ff;
	send_data[i++]=yaw_L;
	yaw_H=Yaw&0xff00;
	yaw_H>>=8;
	send_data[i++]=yaw_H;	
	
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)==0)
		send_data[7]=0X01;

}



void datasend()
{
	u8 i=0;
	send_data[i++]=0xaa;
	send_data[i++]=0x55;
	send_data[i++]=AD3;//Motor
	send_data[i++]=AD2;//serve	
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)==0)
		send_data[i++]=0X01;
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==0)
	send_data[4]=0X00;
}



