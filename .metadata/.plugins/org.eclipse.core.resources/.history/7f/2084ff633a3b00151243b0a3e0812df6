// 文件:MAIN.C//

// 说明:MSP430F5438开发板单片机定时器A设置实验程序

//设置单片机Timer0_A5每毫秒中断一次,翻转LED驱动段//

//在LED驱动端可见频率为500Hz方波//

// 编译:CCS5.2//

// 日期:2013.05.19//

////

//=============================================================//

#include "msp430x54x.h"
#include "clock.h"
#include"adtransfer.h"
#include"pwm.h"
unsigned char speed1[]={0,30,35,40,45,50,55,60,65,70,75,80,85,90};                 //每分钟液滴个数
unsigned int disduty1[]={500,490,452,403,370,336,297,264,215,164,110,64,25,0};   //设定占空比参数
unsigned char cc=0;
unsigned char dd=0;
unsigned int sum=0;
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void)

{

      //freq=speed1[num];
      //pduty=disduty1[num];
         cc=cc+1;
	if(cc==5){
     ADC_Result = ADS_Read()/2;// Read data from ch1,the last time result
   //   _delay_cycles(200000);`
           cc=0;
           dd=dd+1;
	   if(dd<21){
		 sum=sum+ADC_Result;
	   }
	  if(dd==20){
		average=sum/10;
	 	dd=0;
	 	sum=0;
	  }
//        MotorPlus_ON(pduty);
	}


TA0CCR0= (325) - 1;
T_2ms=T_2ms+1;
if(T_2ms==100){
	T_2ms=0;
	second=second+1;
	if(second==60){
		second=0;
		min=min+1;
		if(min==60){
			min=0;
			hour=hour+1;
			if(hour==24){
				hour=0;
			     /*code=key_scan();
			     switch(code){
			     case 1:mode=mode+1;break;
			     case 2:mode=mode-1;break;
			     case 3:hour=hour+1;break;
			     case 4:hour=hour-1;break;
			     case 5:min=min+1;break;
			     case 6:min=min-1;break;
			     case 7:second=second+1;break;
			     case 8:second=second-1;break;
			     default:break;
			     }
			     */
			}
		}
	}
}

}

//***************************************************************************//

////

//函数:Init_CLK(void)//

//功能:初始化主时钟: MCLK = XT2//

////

//***************************************************************************//

void Init_CLK(void)

{

WDTCTL= WDTPW + WDTHOLD; // 关看门狗

P5SEL|= 0x0C; // 端口功能选择振荡器

UCSCTL6&= ~XT2OFF; // 振荡器使能

UCSCTL3|= SELREF_2; // FLLref = REFO

UCSCTL4|= SELA_2; // ACLK=REFO,SMCLK=DCO,MCLK=DCO
/*
do

{

UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 错误标志

SFRIFG1 &= ~OFIFG;

}while(SFRIFG1&OFIFG); // 检测振荡器错误标志
*/
UCSCTL6|= XT2DRIVE0 + XT2DRIVE1; // XT2 驱动模式 24~32MHz

UCSCTL4|= SELS_5 + SELM_5; // SMCLK = MCLK = XT2

}

//***************************************************************************//



//Init_TimerA0(void): 设置TimerA0//

////

//***************************************************************************//

void Init_Timer0_A5(void)

{

TA0CTL= MC_1+TASSEL_1+TACLR;

TA0CCR0=328- 1; // SMCK=EX2=25MHz,设置计数器溢出时间为1ms

TA0CCTL0 = CCIE;

}

//***************************************************************************//

////

//主程序: 初始化时钟、端口和定时器//

////

//***************************************************************************//

void TIMERA0main(void)

{

//WDTCTL = WDTPW + WDTHOLD; // 关闭看门狗

Init_CLK();

Init_Timer0_A5();

//_EINT();

//LPM3;

}









