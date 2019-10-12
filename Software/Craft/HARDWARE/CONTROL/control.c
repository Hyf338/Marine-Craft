#include "sys.h"
#include "stm32f10x.h"
#include "control.h"
#include "timer.h"
#include "delay.h"

#define servo_mid 1210
#define N 5

int Expect_servo=0;
int servo_PWM=1210;
int servo_last=0;
int Servo_err=0;
//---------------------------
u8 infrared=0x00;//��ʼ״̬
char temp=0x00;
char infrared_flag=0;
u8  infrared_bit[8]={0};
int servo_err[4]={0,0,0,0};
u8 sum=0;
int infrared_err=0;

/*�������ų�ʼ������*/
void infrared_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 |GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA
}


/*������λ�ƺ�����
	Ŀ�꣺�Ѱ˸�����ͷ��λ����һ��char�����ݣ�����дswitch��case���
	��ֵ˵����0Ϊ���յ������źţ�1δ���յ��źš����źŵ�״̬Ϊ0xff
*/
	
u8 infrared_bit_move(void)
{
	
	char i=0;
	infrared=0xff;
	temp=0x00;
	
	while(!infrared_flag)
	{
		infrared_bit[0]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);//1-8�ź��ⰴ������
		infrared_bit[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
		infrared_bit[2]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9);
		infrared_bit[3]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8);
		infrared_bit[4]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7);
		infrared_bit[5]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6);
		infrared_bit[6]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
		infrared_bit[7]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14); 
	
		for(i=0;i<8;i++)//��⵽Ϊ0��bit[0] ���λ
		{
			temp = temp<<1;
			temp|=infrared_bit[7-i];
		}
		infrared&=temp;
		
	}
	
	if(infrared_flag==1) infrared_flag=0;
	
	return infrared;
}




/*������մ�����*/
void infrared_receive_1()
{
	infrared=filter();
	switch(infrared)
		
	{
		case 0xfe:Expect_servo=900;break;//1��
		case 0xfd:Expect_servo=900;break;//2
		case 0xfb:Expect_servo=1600;break;//3
		case 0xf7:Expect_servo=1600;break;//4
		case 0xef:Expect_servo=1600;break;//5
		case 0xdf:Expect_servo=1600;break;//6
		case 0xbf:Expect_servo=900;break;//7
		case 0x7f:Expect_servo=1210;break;//8
		
		case 0x7e:Expect_servo=900;break;
		case 0xfc:Expect_servo=900;break;
		case 0xf9:Expect_servo=900;break;
		case 0xf3:Expect_servo=1600;break;
		case 0xe7:Expect_servo=1600;break;
		case 0xcf:Expect_servo=1600;break;
		case 0x9f:Expect_servo=1210;break;
		case 0x3f:Expect_servo=900;break;
		
		case 0x3e:Expect_servo=1200;break;
		case 0x7c:Expect_servo=900;break;
		case 0xf8:Expect_servo=900;break;
		case 0xf1:Expect_servo=1600;break;
		case 0xe3:Expect_servo=1600;break;
		case 0xc7:Expect_servo=1600;break;
		case 0x8f:Expect_servo=900;break;
		case 0x1f:Expect_servo=900;break;
		
		case 0x1e:Expect_servo=900;break;
		case 0x3c:Expect_servo=900;break;
		case 0x78:Expect_servo=900;break;
		case 0xf0:Expect_servo=1600;break;
		case 0xe1:Expect_servo=1600;break;
		case 0xc3:Expect_servo=1600;break;
		case 0x87:Expect_servo=1600;break;
		case 0x0f:Expect_servo=1210;break;
		
		case 0xce:Expect_servo=1600;break;
		case 0x1c:Expect_servo=1600;break;
		case 0x38:Expect_servo=1600;break;
		case 0x70:Expect_servo=1600;break;
		case 0xe0:Expect_servo=900;break;
		case 0xc1:Expect_servo=1200;break;
		case 0x83:Expect_servo=900;break;
		case 0x07:Expect_servo=900;break;
		
		case 0x06:Expect_servo=1210;break;
		case 0x0c:Expect_servo=900;break;
		case 0x18:Expect_servo=900;break;
		case 0x30:Expect_servo=900;break;
		case 0x60:Expect_servo=1600;break;
		case 0xc0:Expect_servo=1600;break;
		case 0x81:Expect_servo=1600;break;
		case 0x03:Expect_servo=1600;break;
		
		case 0x02:Expect_servo=1600;break;
		case 0x04:Expect_servo=900;break;
		case 0x08:Expect_servo=1200;break;
		case 0x10:Expect_servo=900;break;
		case 0x20:Expect_servo=900;break;
		case 0x40:Expect_servo=1600;break;
		case 0x80:Expect_servo=1600;break;
		case 0x01:Expect_servo=1600;break;

		
		default:Expect_servo=Expect_servo;break;
	}
	
	 Expect_servo= (Expect_servo>1600)? 1600:Expect_servo;
	 Expect_servo= (Expect_servo<850)? 850:Expect_servo;

}

//����2����ʹ��case��䣬
void infrared_receive_2()
{
	u8 i=0;
	sum=0;
	infrared=filter();
	infrared_err+=(infrared|0x7f)==0x7f? 400:0;//300:0;	//8��
	infrared_err+=(infrared|0xbf)==0xbf? 400:0;//150:0; //7��
	infrared_err+=(infrared|0xdf)==0xdf? -300:0;//-150:0;		//6��
	infrared_err+=(infrared|0xef)==0xef? -300:0;//-300:0;//5��
	infrared_err+=(infrared|0xfe)==0xfe? -300:0;//-300:0;//4��
	infrared_err+=(infrared|0xfd)==0xfd? -300:0;//-300:0;//3��
	infrared_err+=(infrared|0xfb)==0xfb? 400:0;//300:0;
	infrared_err+=(infrared|0xf7)==0xf7? 400:0;//300:0;
	
	for(i=0;i<8;i++)
	{
		sum+=(infrared>>i)&1;//��1�ĸ���
	}
	sum=8-sum;//��0�ĸ���
	if(sum!=0)//�н���
	{
		Expect_servo=(int)(servo_mid-infrared_err/sum);
	}
	
	 Expect_servo= (Expect_servo>1600)? 1600:Expect_servo;
	 Expect_servo= (Expect_servo<850)? 850:Expect_servo;
}

char filter(void)
{

   char value_buf[N];
   char count,i,j,temp;
   for ( count=0;count<N;count++)
   {
      value_buf[count] = infrared_bit_move();
   }
   for (j=0;j<N-1;j++)
   {
      for (i=0;i<N-j;i++)
      {
         if ( value_buf[i]>value_buf[i+1] )
         {
            temp = value_buf[i];
            value_buf[i] = value_buf[i+1]; 
             value_buf[i+1] = temp;
         }
      }
   }
   return value_buf[(N-1)/2];
}


void servo_PD()
{
	 u8 i=0;
//	 static int expect_s[3]={0,       0,0};
	 u8 servo_p=1;//10Ϊ��ֵ
	 u8 servo_d=1;//10Ϊ��ֵ
	 
	 servo_err[3]=(int)(servo_p*(Expect_servo-servo_mid)+servo_d*(servo_err[3]-servo_last));
	 servo_last=servo_err[3];
	 
	 for(i=0;i<2;i++)
	 servo_err[i]=servo_err[i+1];//�����˲�
   Servo_err=0.85*servo_err[3]+0.08*servo_err[2]+0.05*servo_err[1]+0.02*servo_err[0];
	 servo_PWM=servo_mid-Servo_err;
	 servo_PWM= (servo_PWM>1600)? 1600:servo_PWM;
	 servo_PWM= (servo_PWM<850)? 850:servo_PWM;
}






