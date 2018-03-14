#include <msp430.h>
#include "MSP430X54X.h"
#include "lcddisplay.h"
#include "keyscan.h"
#include "clc_Init.h"
#include "pwm.h"
#include "fourkey.h"
#include "clock.h"
#include "adtransfer.h"
#include"pidctl.h"

unsigned char SmileFace[]={0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char speed[]={0,30,35,40,45,50,55,60,65,70,75,80,85};                 //每分钟液滴个数
unsigned int disduty[]={500,452,403,370,336,297,264,215,164,110,64,25,0};   //设定占空比参数
unsigned char hour=0;
unsigned char min=0;
unsigned char second=0;
unsigned char T_2ms=0;
unsigned int act_time=0;
unsigned char num=0;
unsigned char freq=0;

unsigned int pduty=600;
unsigned int mode=1;
unsigned int mode1=2;
unsigned int average=0;
unsigned char i=1;
unsigned char j=0;
int code=0;
unsigned char keycode=0;
volatile int ADC_Result;
volatile int ADC_SET;
unsigned int set_average=0;
unsigned int set_sum=0;
			  float Voltage_ch1;
unsigned int showspeed=0;
/*
 * main.c`
 */
int main(void) {
   WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog `timer
 // ` CLK_Init();

    PORT_Init();
    GPIO2_Init();
    SPI_Init();
    ADS_Config();
	lcd_Init();
	clc_lcd();
    GPIO_int();

    _enable_interrupts();
   // _bis_SR_register(LPM3_bits);
	 // _EINT();`
	//_enable_interrupts();



   pduty=500;
	while(1){
		if(mode!=mode1){
		clc_lcd();
		}
		mode1=mode;
		displayspeed();

		//config ch2
     code=key_scan();
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


		//ADC_Result = ADS_Read();

		if(mode==1){
			for(i=1;i<4;i++){
				for(j=0;j<8;j++){
					gotoxy(i,j);
					code=SmileFace[8*i+j-8];
				}
			}
		}
		if(mode==2){
			gotoxy(2,0);
				showstr("检测当前光电条件");
				gotoxy(3,1);
				showstr("请等待……");
				 TB0_PWM_SetPeriod(500);
				 MotorPlus_ON(0);
				 _delay_cycles(5000000);
				unsigned char ee=0;

				for(ee=0;ee<29;ee++){
				    _delay_cycles(1000000);
                    if(ee>8){
				    ADC_SET=ADS_Read()/2;

				    set_sum=set_sum+ADC_SET;
				}
				}
				set_average=set_sum/10;
				set_sum=0;
                mode=mode+1;
                MotorPlus_ON(1000);
		}
		if(mode==3)
		{
		    TIMERA0main();
		    TA0CCTL0=0;
        freq=speed[num];
      // pduty=disduty[num];
    // TB0_PWM_SetPeriod(500);
    //    MotorPlus_ON(pduty);
      //  pduty=disduty[num];

     //   MotorPlus_ON(pduty);
		gotoxy(1,0);
		showstr("时分秒");
		gotoxy(1,4);
		showstr(":");
		gotoxy(1,6);
		showstr(":");
		gotoxy(2,0);
		showstr("输液次数:");
		gotoxy(2,5);
		wr_lcd(freq/10+48,1);
		wr_lcd(freq%10+48,1);
		gotoxy(2,6);
		showstr(" /分");
		gotoxy(3,0);
		showstr("输液提示: 配置");

		//时分秒设置
		gotoxy(1,3);
		wr_lcd(hour/10+48,1);
		wr_lcd(hour%10+48,1);
		gotoxy(1,5);
		wr_lcd(min/10+48,1);
		wr_lcd(min%10+48,1);
		gotoxy(1,7);
		wr_lcd(second/10+48,1);
		wr_lcd(second%10+48,1);

		gotoxy(4,0);
		wr_lcd(mode+48,1);
		}

		if (mode==4){
			TA0CCTL0=CCIE;
		           freq=speed[num];

	               TB0_PWM_SetPeriod(500);
	               MotorPlus_ON(pduty);
		      //  pduty=disduty[num];`

		     //   MotorPlus_ON(pduty);
				gotoxy(1,0);
				showstr("时分秒");
				gotoxy(1,4);
				showstr(":");
				gotoxy(1,6);
				showstr(":");
				gotoxy(2,0);
				showstr("输液次数:");
				gotoxy(2,5);
				wr_lcd(freq/10+48,1);
				wr_lcd(freq%10+48,1);
				gotoxy(2,6);
				showstr(" /分");
				gotoxy(3,0);
				showstr("输液提示: 正在输");

				//时分秒设置
				gotoxy(1,3);
			wr_lcd(hour/10+48,1);
				wr_lcd(hour%10+48,1);
				gotoxy(1,5);
				wr_lcd(min/10+48,1);
				wr_lcd(min%10+48,1);
				gotoxy(1,7);
				wr_lcd(second/10+48,1);
				wr_lcd(second%10+48,1);

				gotoxy(4,0);
				wr_lcd(mode+48,1);

				gotoxy(4,2);
				showstr("speed:");
				gotoxy(4,5);
				wr_lcd(act_time/10+48,1);
				wr_lcd(act_time%10+48,1);
		}
		if(mode>2|mode<1){
			gotoxy(4,0);
			wr_lcd(mode+48,1);
		}
	    piadjust();
	}

}
