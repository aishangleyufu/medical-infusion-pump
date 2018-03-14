/*
 * clc_Init.c
 *
 *  Created on: 2015年7月30日
 *      Author: c
 */
#include "MSP430X54X.h"
#define uchar unsigned char
#define uint unsigned int
void CLK_Init(void) //时钟初始化配置
{
//unsigned int i;
P5SEL|=BIT2+BIT3; //P5.2.3口选择连接XT2
P7SEL|=BIT0+BIT1; //P7.0.1口选择连接XT1
UCSCTL0=0x0000; //方便自带调节
UCSCTL1=DCORSEL_5; //选择DC0工作范围
UCSCTL2=FLLD_1+374; //DCOCLK 分频D=2，N+1=375，DCOCLk=D*（N+1）*DCOREFCLk/n
UCSCTL3|=FLLREFDIV_1; //选择DCO参考频率为n=2,
UCSCTL6&=~(XT1OFF+XT2OFF); // 开XT1，XT2
UCSCTL6|=XCAP_3; //配置XT1内部电容12Pf
UCSCTL6|=XT2DRIVE_2; //增大XT2的驱动能力
/*while((SFRIFG1&OFIFG)!=0){
SFRIFG1&=~OFIFG; //清除振荡器错误标志位
UCSCTL7&=~(XT2OFFG+XT1LFOFFG+XT1HFOFFG +DCOFFG);
//清除XT1，XT2,DCO 错误标志位
for(i=0xff;i>0;i--);
}*/
UCSCTL4=SELA_0+SELS_5+SELM_5;
//ACLK选择XT1=32768Hz,SMCLK=XT2,MCLK=XT2 为16MHz
UCSCTL5|=DIVS_0+DIVM_0;
}

void PORT_Init(void)
{
	//键盘部分
	//P6DIR=0x0f; //P2 低四位设置为输出
	//P6REN=0xf0; //P2口电阻上拉
	//P6OUT=0xf0; //P2高位拉高
	//P6IES=0xf0; //P2高四位下降沿中断
	//P6IFG=0x00; //P2 中断标志清零
	//P6IE=0xf0; //P2口高四位中断使能

	//-----配合机械按键，启用内部上拉电阻-----
	//P11REN |= BIT1+BIT2;				        //启用P1.3内部上下拉电阻
	//P11OUT |= BIT1+BIT2;			            //将电阻设置为上拉
	//-----配置P1.3中断参数-----
	//P1DIR&= ~BIT6;              // P1.3设为输入(可省略)
	//P1DIR&=~BIT7;
	//P1IES |= BIT6;                          // P1.3设为下降沿中断
	//P1IE |= BIT6;                          // 允许P1.3中断

	//液晶部分
	P3DIR|=0x31; //P3.0.5.4 设置为输出,用于控制12864 的读写，片选，
	P8DIR|=0xff; //P9 口设置成输出，用于12864 的数据口
	P11OUT&=~BIT0;
	//P11OUT|=BIT0;
}




