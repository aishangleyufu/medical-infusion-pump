/*``
 * pwm.c
 *
 *  Created on: 2015��8��2��
 *      Author: c
 */

/*
 * PWM.c
 *
 *  Created on: Jul 31, 2015
 *  				8:43PM
 *      Author: Hebral
 */
/*����Ӳ��������ͼ����֪����drv8412��ģʽѡ��MOM1M2���Ѿ�Ĭ��Ϊ0�ӵ�
*			driver model�� ˫·ȫ�ţ�����PWM����ÿ��ȫ�ţ����ĸ����������ڵ�������
 * 			JG3/TB0.3/P4.3-----PWM-C
 * 			JG3/TB0.4/P4.4-----PWM-D
 *
 */
#include<msp430f5438a.h>
#include "PWM.h"

#define DEADTIME 20							//Ԥ������ʱ�䣬��TA��clkΪ��λ
/*****�趨TB�����IO��*/
#define PWM_C_ON 		P4SEL |= BIT3; P4DIR |= BIT3		//P4.3
#define PWM_C_OFF 		P4SEL&= ~BIT3 							//P4.3
#define PWM_D_ON 		P4SEL |= BIT4; P4DIR |= BIT4		//P4.4
#define PWM_D_OFF 		P4SEL&= ~BIT4 							//P4.4
#define OUTPUT34_0		P4DIR |= BIT3 + BIT4;	P4OUT &= ~(BIT3 + BIT4)
#define PWM_PERIOD		250
/******************************************************************************************************
* ��       �ƣ�TB0_PWM_Init()
* ��       �ܣ�TB0��ʱ����ΪPWM�������ĳ�ʼ�����ú���
* ��ڲ����� Clk:ʱ��Դ 'S'=SMCLK;   'A'=ACLK ;   'E'=TACLK(�ⲿ����)�� 'e'= TACLK(TACLKȡ��)
                    Div:ʱ�ӷ�Ƶϵ��: 1/2/4/8
		    Mode_C:ͨ��PWM_C�����ģʽ 'F'��Ϊ��ǰPWM��ģʽ7����'B'�ͺ�PWM��ģʽ3�� ��'D'��������PWM��ģʽ6����0=����
		    Mode_D:ͨ��PWM_D�����ģʽ 'F'��Ϊ��ǰPWM��ģʽ7����'B'�ͺ�PWM ��ģʽ3����'D'��������PWM��ģʽ2����0=����
		    ����������������Ƶ�PWMʱ����ͨ������ʹ�ã��Ҿ�Ϊ����ģʽ��
* ���ڲ�����1��ʾ���óɹ���0��ʾ������������ʧ�ܡ�
* ˵       �� : �ڵ���PWM��غ���֮ǰ����Ҫ���øú�������TA��ģʽ��ʱ��Դ��
* ��       �� : TB0_PWM_Init('A',1,'F','P')TAʱ����ΪACLK,ͨ��1��ͨ��2��Ϊ��ǰPWM���
                   TB0_PWM_Init('S',4,'D','D')TAʱ����ΪSMCLK/4, ͨ��1Ϊ������PWM��ͨ��2Ϊ������PWM
                   TB0_PWM_Init('A',1,'F',0)TAʱ����ΪACLK,ͨ��1��ǰPWM�����ͨ��2����TA�á�
 ******************************************************************************************************/
char TB0_PWM_Init(char Clk,char Div,char Mode1,char Mode2)
{
  TB0CTL =0;																			// �����ǰ����
  if((Mode1 == '0') && (Mode2 == '0'))
	  return (0);
  switch(Mode1)																	//Ϊ��ʱ��ѡ�����ģʽ
  {
  case 'F': case 'f':																//��ͨPWM
		  TB0CTL |=MC_1; break;											//����ʱ��Ϊ������
  case 'B':case 'b':
	  	  TB0CTL |=MC_1; break;											//����ʱ��Ϊ������
  case 'D': case 'd':															//����PWM
     	  TB0CTL |=MC_3; break;											//����ʱ��Ϊ��������
  default : break;															//��������������ò������󣬷���0
  }
  switch(Mode2)																	//Ϊ��ʱ��ѡ�����ģʽ
  {
  case 'F': case 'f':																//��ͨPWM
		  TB0CTL |=MC_1; break;											//����ʱ��Ϊ������
  case 'B':case 'b':
	  	  TB0CTL |=MC_1; break;											//����ʱ��Ϊ������
  case 'D': case 'd':															//����PWM
     	  TB0CTL |=MC_3; break;											//����ʱ��Ϊ��������
  default : break;															//��������������ò������󣬷���0
  }

  switch(Clk)  																		//Ϊ��ʱ��TAѡ��ʱ��Դ
  {
    case 'A': case 'a':  	TB0CTL|=TBSSEL_1; break;   			//ACLK
    case 'S': case 's': 		TB0CTL|=TBSSEL_2; break;  			//SMCLK
    case 'E':            		TB0CTL|=TBSSEL_0; break;  			//�ⲿ����(TACLK)
    case 'e':          			TB0CTL|=TBSSEL_3; break;   			//�ⲿ����(TACLKȡ��)
    default :  return(0);	 														//���ò������󣬷���0
  }
  switch(Div) 																		//Ϊ��ʱ��TAѡ���Ƶϵ��
  {
    case 1:   TB0CTL|=ID_0; break;   //1
    case 2:   TB0CTL|=ID_1; break;   //2
    case 4:   TB0CTL|=ID_2; break;   //4
    case 8:   TB0CTL|=ID_3; break;   //8
    default :  return(0);  														//���ò������󣬷���0
  }
  switch(Mode1)										 							//����PWMͨ��1�����ģʽ��
  {
     case 'F':	case 'f':
              TB0CCTL3 = OUTMOD_7;
              PWM_C_ON;
              break;
     case 'B':	case 'b':
              TB0CCTL3 = OUTMOD_3;
              PWM_C_ON;
              break;
     case 'D': case'd':
			 TB0CCTL3 = OUTMOD_6;
			 PWM_C_ON;
    	     break;
      case '0':case 0:   															//�������Ϊ����
    	  	  PWM_C_OFF;   															//TA0.1�ָ�Ϊ��ͨIO��
              break;
     default :  return(0); 							  							//���ò������󣬷���0
  }
  switch(Mode2) 																//����PWMͨ��2�����ģʽ��
  {
      case 'F':	 case 'f':
              TB0CCTL4 = OUTMOD_7;
              PWM_D_ON;  break;
       case 'B':	case 'b':
              TB0CCTL4 = OUTMOD_3;
              PWM_C_ON;
               break;
       case 'D': case 'd':
	       	   TB0CCTL4 = OUTMOD_2;
	       	   PWM_C_ON;
	       	   break;
       case '0':case 0:   														//�������Ϊ����
    	   	   PWM_C_OFF;   							 						//TA0.1�ָ�Ϊ��ͨIO��
           	 	break;
       default :  return(0); 												//���ò������󣬷���0
    }
  return(1);
}
/******************************************************************************************************
* ��       �ƣ�TB0_PWM_SetPeriod()
* ��       �ܣ�����PWM������������
* ��ڲ�����Channel: TA0=0, TA1=1
*                     Period:����(0~65535) ʱ�Ӹ���
* ���ڲ�����1�����óɹ�     0������ʧ��
* ˵       �� : ��ͨPWM�������PWM�������һ��
* ��       �� : TA0_PWM_SetPeriod(500)����PWM��������Ϊ500��1000��ʱ������
 ******************************************************************************************************/
char TB0_PWM_SetPeriod(unsigned int Period)
{
	if (Period>65535)	return(0);
	 TB0CCR0 = Period;
	return(1);
}
/******************************************************************************************************
* ��    �ƣ�TB0_PWM_SetPermill()
* ��    �ܣ�����PWM�����ռ�ձ�(ǧ�ֱ�)
* ��ڲ����� Channel: ��ǰ���õ�ͨ����  1/2
            		Duty: PWM�ߵ�ƽ��Чʱ���ǧ�ֱ� (0~1000)��
* ���ڲ�����1���óɹ���0����ʧ��
* ˵    ��: 1000=100.0%  500=50.0% ���������ơ�����ģʽʱ����channelͬʱ�趨��
* ��    ��: TA0_PWM_SetPermill(1,300)����PWMͨ��1������ռ�ձ�Ϊ30.0%
               TA0_PWM_SetPermill(2,,825)����PWMͨ��2������ռ�ձ�Ϊ82.5%
 ******************************************************************************************************/
char TB0_PWM_SetPermill(char Channel,unsigned int Duty)
{
	unsigned char Mod = 0;
	unsigned int DeadPermill=0;
	unsigned long int Percent=0;							//��ֹ�˷�����ʱ���
	Percent=Duty;
	DeadPermill=((DEADTIME*1000)/TBCCR0);		//����������ʱ�任���ǧ�ֱ�����ʱ��
	switch (Channel)												//���жϳ�ͨ���Ĺ���ģʽ
		{
	case 1:
		Mod = (TB0CCTL3& 0x00e0)>>5;		break;	//��ȡ���ģʽ��OUTMOD0λ��5-7λ
	case 2:
		Mod = (TB0CCTL4 & 0x00e0)>>5;	break;	//��ȡ���ģʽ��OUTMOD1λ��5-7λ
	default:	return(0);
		}

	switch(Mod)														//����ģʽ�趨TACCRx
		{
	case 2: case 6:			/**����ģʽ2,6ʱ����Ҫ�ж���������ʱ�䣬��ͬʱ�趨TA0CCR1/2 ��ֵ*/
		{
			if((1000-2*Percent)<=DeadPermill)					//Ԥ������ʱ��--------���Ҵ�������
				Percent=(1000-DeadPermill)/2;
			TB0CCR3=Percent*TB0CCR0/1000;
			TB0CCR4= TB0CCR0-TB0CCR3;
			break;
		}
		case 7:
		{
			if(Percent>1000)	Percent=1000;
			if(Channel==1) TB0CCR3=Percent* TB0CCR0/1000;
			if(Channel==2) TB0CCR4=Percent* TB0CCR0/1000;
			break;
		}
		case 3:		//ռ�ձ�һ��Ϊ������������Ҫ TA0CCR0��ȥռ�ձ�
		{
			if(Percent>1000)	Percent=1000;
			if(Channel==1) TB0CCR3= TB0CCR0-Percent*TB0CCR0/1000;
			if(Channel==2) TB0CCR4= TB0CCR0-Percent*TB0CCR0/1000;
			break;
		}
		default: return(0);
		}
		return (1);
	}

void MotorPlus_ON(int duty1)				//duty  Ϊռ�ձ�
{
	int  duty0;
	duty0 = duty1;
	TB0_PWM_Init('S',1,'F','F');
	TB0_PWM_SetPeriod(PWM_PERIOD);				//�趨PWM����
	TB0_PWM_SetPermill(1,duty0);
	TB0_PWM_SetPermill(2,0);
}

void MotorNeg_ON(int duty2)				//duty  Ϊռ�ձ�
{
	int  duty3;
	duty3 = duty2;
	TB0_PWM_SetPeriod(PWM_PERIOD);				//�趨PWM����
	TB0_PWM_Init('S',1,'F','F');
	TB0_PWM_SetPermill(1,0);
	TB0_PWM_SetPermill(2,duty3);
}



