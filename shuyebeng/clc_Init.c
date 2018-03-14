/*
 * clc_Init.c
 *
 *  Created on: 2015��7��30��
 *      Author: c
 */
#include "MSP430X54X.h"
#define uchar unsigned char
#define uint unsigned int
void CLK_Init(void) //ʱ�ӳ�ʼ������
{
//unsigned int i;
P5SEL|=BIT2+BIT3; //P5.2.3��ѡ������XT2
P7SEL|=BIT0+BIT1; //P7.0.1��ѡ������XT1
UCSCTL0=0x0000; //�����Դ�����
UCSCTL1=DCORSEL_5; //ѡ��DC0������Χ
UCSCTL2=FLLD_1+374; //DCOCLK ��ƵD=2��N+1=375��DCOCLk=D*��N+1��*DCOREFCLk/n
UCSCTL3|=FLLREFDIV_1; //ѡ��DCO�ο�Ƶ��Ϊn=2,
UCSCTL6&=~(XT1OFF+XT2OFF); // ��XT1��XT2
UCSCTL6|=XCAP_3; //����XT1�ڲ�����12Pf
UCSCTL6|=XT2DRIVE_2; //����XT2����������
/*while((SFRIFG1&OFIFG)!=0){
SFRIFG1&=~OFIFG; //������������־λ
UCSCTL7&=~(XT2OFFG+XT1LFOFFG+XT1HFOFFG +DCOFFG);
//���XT1��XT2,DCO �����־λ
for(i=0xff;i>0;i--);
}*/
UCSCTL4=SELA_0+SELS_5+SELM_5;
//ACLKѡ��XT1=32768Hz,SMCLK=XT2,MCLK=XT2 Ϊ16MHz
UCSCTL5|=DIVS_0+DIVM_0;
}

void PORT_Init(void)
{
	//���̲���
	//P6DIR=0x0f; //P2 ����λ����Ϊ���
	//P6REN=0xf0; //P2�ڵ�������
	//P6OUT=0xf0; //P2��λ����
	//P6IES=0xf0; //P2����λ�½����ж�
	//P6IFG=0x00; //P2 �жϱ�־����
	//P6IE=0xf0; //P2�ڸ���λ�ж�ʹ��

	//-----��ϻ�е�����������ڲ���������-----
	//P11REN |= BIT1+BIT2;				        //����P1.3�ڲ�����������
	//P11OUT |= BIT1+BIT2;			            //����������Ϊ����
	//-----����P1.3�жϲ���-----
	//P1DIR&= ~BIT6;              // P1.3��Ϊ����(��ʡ��)
	//P1DIR&=~BIT7;
	//P1IES |= BIT6;                          // P1.3��Ϊ�½����ж�
	//P1IE |= BIT6;                          // ����P1.3�ж�

	//Һ������
	P3DIR|=0x31; //P3.0.5.4 ����Ϊ���,���ڿ���12864 �Ķ�д��Ƭѡ��
	P8DIR|=0xff; //P9 �����ó����������12864 �����ݿ�
	P11OUT&=~BIT0;
	//P11OUT|=BIT0;
}




