/*``
 * pwm.c
 *
 *  Created on: 2015年8月2日
 *      Author: c
 */

/*
 * PWM.c
 *
 *  Created on: Jul 31, 2015
 *  				8:43PM
 *      Author: Hebral
 */
/*根据硬件的连接图可以知道，drv8412的模式选择MOM1M2，已经默认为0接地
*			driver model： 双路全桥（两个PWM输入每个全桥）或四个半桥逐周期电流限制
 * 			JG3/TB0.3/P4.3-----PWM-C
 * 			JG3/TB0.4/P4.4-----PWM-D
 *
 */
#include<msp430f5438a.h>
#include "PWM.h"

#define DEADTIME 20							//预设死区时间，以TA的clk为单位
/*****设定TB输出的IO口*/
#define PWM_C_ON 		P4SEL |= BIT3; P4DIR |= BIT3		//P4.3
#define PWM_C_OFF 		P4SEL&= ~BIT3 							//P4.3
#define PWM_D_ON 		P4SEL |= BIT4; P4DIR |= BIT4		//P4.4
#define PWM_D_OFF 		P4SEL&= ~BIT4 							//P4.4
#define OUTPUT34_0		P4DIR |= BIT3 + BIT4;	P4OUT &= ~(BIT3 + BIT4)
#define PWM_PERIOD		250
/******************************************************************************************************
* 名       称：TB0_PWM_Init()
* 功       能：TB0定时器作为PWM发生器的初始化设置函数
* 入口参数： Clk:时钟源 'S'=SMCLK;   'A'=ACLK ;   'E'=TACLK(外部输入)； 'e'= TACLK(TACLK取反)
                    Div:时钟分频系数: 1/2/4/8
		    Mode_C:通道PWM_C的输出模式 'F'设为超前PWM（模式7），'B'滞后PWM（模式3） ，'D'带死区增PWM（模式6），0=禁用
		    Mode_D:通道PWM_D的输出模式 'F'设为超前PWM（模式7），'B'滞后PWM （模式3），'D'带死区减PWM（模式2），0=禁用
		    设置输出带死区控制的PWM时，两通道均需使用，且均为死区模式。
* 出口参数：1表示设置成功，0表示参数错误，设置失败。
* 说       明 : 在调用PWM相关函数之前，需要调用该函数设置TA的模式和时钟源。
* 范       例 : TB0_PWM_Init('A',1,'F','P')TA时钟设为ACLK,通道1和通道2均为超前PWM输出
                   TB0_PWM_Init('S',4,'D','D')TA时钟设为SMCLK/4, 通道1为死区增PWM、通道2为死区减PWM
                   TB0_PWM_Init('A',1,'F',0)TA时钟设为ACLK,通道1超前PWM输出，通道2不作TA用。
 ******************************************************************************************************/
char TB0_PWM_Init(char Clk,char Div,char Mode1,char Mode2)
{
  TB0CTL =0;																			// 清除以前设置
  if((Mode1 == '0') && (Mode2 == '0'))
	  return (0);
  switch(Mode1)																	//为定时器选择计数模式
  {
  case 'F': case 'f':																//普通PWM
		  TB0CTL |=MC_1; break;											//主定时器为增计数
  case 'B':case 'b':
	  	  TB0CTL |=MC_1; break;											//主定时器为增计数
  case 'D': case 'd':															//死区PWM
     	  TB0CTL |=MC_3; break;											//主定时器为增减计数
  default : break;															//其他情况都是设置参数有误，返回0
  }
  switch(Mode2)																	//为定时器选择计数模式
  {
  case 'F': case 'f':																//普通PWM
		  TB0CTL |=MC_1; break;											//主定时器为增计数
  case 'B':case 'b':
	  	  TB0CTL |=MC_1; break;											//主定时器为增计数
  case 'D': case 'd':															//死区PWM
     	  TB0CTL |=MC_3; break;											//主定时器为增减计数
  default : break;															//其他情况都是设置参数有误，返回0
  }

  switch(Clk)  																		//为定时器TA选择时钟源
  {
    case 'A': case 'a':  	TB0CTL|=TBSSEL_1; break;   			//ACLK
    case 'S': case 's': 		TB0CTL|=TBSSEL_2; break;  			//SMCLK
    case 'E':            		TB0CTL|=TBSSEL_0; break;  			//外部输入(TACLK)
    case 'e':          			TB0CTL|=TBSSEL_3; break;   			//外部输入(TACLK取反)
    default :  return(0);	 														//设置参数有误，返回0
  }
  switch(Div) 																		//为定时器TA选择分频系数
  {
    case 1:   TB0CTL|=ID_0; break;   //1
    case 2:   TB0CTL|=ID_1; break;   //2
    case 4:   TB0CTL|=ID_2; break;   //4
    case 8:   TB0CTL|=ID_3; break;   //8
    default :  return(0);  														//设置参数有误，返回0
  }
  switch(Mode1)										 							//设置PWM通道1的输出模式。
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
      case '0':case 0:   															//如果设置为禁用
    	  	  PWM_C_OFF;   															//TA0.1恢复为普通IO口
              break;
     default :  return(0); 							  							//设置参数有误，返回0
  }
  switch(Mode2) 																//设置PWM通道2的输出模式。
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
       case '0':case 0:   														//如果设置为禁用
    	   	   PWM_C_OFF;   							 						//TA0.1恢复为普通IO口
           	 	break;
       default :  return(0); 												//设置参数有误，返回0
    }
  return(1);
}
/******************************************************************************************************
* 名       称：TB0_PWM_SetPeriod()
* 功       能：设置PWM发生器的周期
* 入口参数：Channel: TA0=0, TA1=1
*                     Period:周期(0~65535) 时钟个数
* 出口参数：1：设置成功     0：设置失败
* 说       明 : 普通PWM与带死区PWM周期相差一倍
* 范       例 : TA0_PWM_SetPeriod(500)设置PWM方波周期为500或1000个时钟周期
 ******************************************************************************************************/
char TB0_PWM_SetPeriod(unsigned int Period)
{
	if (Period>65535)	return(0);
	 TB0CCR0 = Period;
	return(1);
}
/******************************************************************************************************
* 名    称：TB0_PWM_SetPermill()
* 功    能：设置PWM输出的占空比(千分比)
* 入口参数： Channel: 当前设置的通道号  1/2
            		Duty: PWM高电平有效时间的千分比 (0~1000)，
* 出口参数：1设置成功，0设置失败
* 说    明: 1000=100.0%  500=50.0% ，依次类推。死区模式时，两channel同时设定。
* 范    例: TA0_PWM_SetPermill(1,300)设置PWM通道1方波的占空比为30.0%
               TA0_PWM_SetPermill(2,,825)设置PWM通道2方波的占空比为82.5%
 ******************************************************************************************************/
char TB0_PWM_SetPermill(char Channel,unsigned int Duty)
{
	unsigned char Mod = 0;
	unsigned int DeadPermill=0;
	unsigned long int Percent=0;							//防止乘法运算时溢出
	Percent=Duty;
	DeadPermill=((DEADTIME*1000)/TBCCR0);		//将绝对死区时间换算成千分比死区时间
	switch (Channel)												//先判断出通道的工作模式
		{
	case 1:
		Mod = (TB0CCTL3& 0x00e0)>>5;		break;	//读取输出模式，OUTMOD0位于5-7位
	case 2:
		Mod = (TB0CCTL4 & 0x00e0)>>5;	break;	//读取输出模式，OUTMOD1位于5-7位
	default:	return(0);
		}

	switch(Mod)														//根据模式设定TACCRx
		{
	case 2: case 6:			/**死区模式2,6时，需要判断修正死区时间，且同时设定TA0CCR1/2 的值*/
		{
			if((1000-2*Percent)<=DeadPermill)					//预留死区时间--------尚且存在问题
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
		case 3:		//占空比一律为正脉宽，所以需要 TA0CCR0减去占空比
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

void MotorPlus_ON(int duty1)				//duty  为占空比
{
	int  duty0;
	duty0 = duty1;
	TB0_PWM_Init('S',1,'F','F');
	TB0_PWM_SetPeriod(PWM_PERIOD);				//设定PWM周期
	TB0_PWM_SetPermill(1,duty0);
	TB0_PWM_SetPermill(2,0);
}

void MotorNeg_ON(int duty2)				//duty  为占空比
{
	int  duty3;
	duty3 = duty2;
	TB0_PWM_SetPeriod(PWM_PERIOD);				//设定PWM周期
	TB0_PWM_Init('S',1,'F','F');
	TB0_PWM_SetPermill(1,0);
	TB0_PWM_SetPermill(2,duty3);
}



