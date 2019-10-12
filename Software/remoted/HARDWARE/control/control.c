#include "control.h"
#include "sys.h"

#include "mpuiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "usart.h"
#include "oled.h"

/*
	pitch    short     						原始数据
	Pitch    signed short int     强制转化成有符号16位
	pitch_L  short int        		低八位
*/

u8 send_data[8]={0,0,0,0,0,0,0,0};
signed short int test_1=0;
int test_size=0;
signed short int pitch_L=0,pitch_H=0,roll_L=0,roll_H=0,yaw_L=0,yaw_H=0;
signed short int Pitch=0,Roll=0,Yaw=0;


extern float pitch,roll,yaw; 		//欧拉角									//俯仰角		翻滚角		横向角
extern short aacx,aacy,aacz;		//加速度传感器原始数据
extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据
extern short temp;					//温度
extern short AD1,AD2,AD3,AD4;

void BUZZ_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA,PD端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);						 //PA.8 输出高
}
 


void angle_get()
{
	if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
	{ 
		temp=MPU_Get_Temperature();	//得到温度值
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
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



