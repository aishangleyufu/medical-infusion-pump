/*
 * lcddisplay.c
 *
 *`  `Created on: 2015��7��29��
 *      Author: c
 */

/*
 * lcddisplay.c
 *
 *  Created on: 2015��7��29��
 *      Author: c
 */
#include"MSP430X54X.h"
#include"lcddisplay.h"
#include"pidctl.h"
#define uchar unsigned char
#define lcddate P8OUT
#define EH P3OUT|=BIT4
#define EL P3OUT&=~BIT4
#define RWH P3OUT|=BIT5
#define RWL P3OUT&=~BIT5
#define RSH P3OUT|=BIT0
#define RSL P3OUT&=~BIT0
#define lcd_rst P11OUT&BIT0

void busy_lcd(void) //���Һ��æ�ź�
{
P8DIR&=~BIT7; //��`�ݿڵ�P8.7 ����Ϊ�����ȡæ�ź�
RSL;
RWH; //01 ��æ�ź�`
EH;
;
;
while(P8IN&0x80); //e �ߵ�ƽ����
EL;
P8DIR|=BIT7;
}

//`Һ��д���ݣ�`ָ���ӳ���
void wr_lcd(uchar DATA,uchar flog)
{
    busy_lcd();   //10д����
    if(flog==0)
	RSL; //flog 0Ϊָ�1Ϊ����
	else
	RSH;

	RWL;
	EH;
	;
	lcddate=DATA;
	;
	EL;
}

void lcd_Init(void) //1286`4 Һ����ʼ��
{
wr_lcd(0x30,0); //�����趨Ϊ����ָ�
//__delay_cycles(1000);
wr_lcd(0x0c,0); //����ʾ���α� 0x08 ����ʾ
//__delay_cycles(1000);
wr_lcd(0x01,0); //�����ʾ
//__delay_cycles(1000);
wr_lcd(0x06,0); //�趨�α��ƶ�����
//__delay_cycles(1000);
}



void clc_lcd(void) //12864 ����
{
wr_lcd(0x30,0);
wr_lcd(0x01,0); //��DDRAM
}
//��Ҫ��ɶ�Һ����������ʹҺ�������ٴ�������ʾ.

void gotoxy(unsigned char y, unsigned char x) //ָ����ʾλ��
{
if(y==1)
wr_lcd(0x80|x,0); //��һ��
if(y==2)
wr_lcd(0x90|x,0); //�ڶ���
if(y==3)
wr_lcd((0x80|x)+8,0); //������
if(y==4)
wr_lcd((0x90|x)+8,0); //������
}

//�ַ�����ʾ�ӳ���`��
void showstr(uchar *str) //��ʾ�ַ�������
{
while(*str!='\0')
{
wr_lcd(*str,1); //д������
str++;
}
}


void displaysz(uchar n,uchar *a) //��ʾһ������
{
uchar i;
for(i=0;i<n;i++)wr_lcd(a[i],1);
}
//������`��Ҫ��һ�����ֵĸ���λ��`����ȡ����֮������Һ����ʾ


void displayspeed(void)
{

	unsigned int standard;
	standard=showspeed;
	unsigned int setside;
	unsigned int maxad=set_average;
	unsigned int minad=maxad-29;
	setside=2*maxad-86;
       if(standard>minad-5&&standard<maxad+5){
    	   act_time=(2*standard-setside);
       }
       if(standard>maxad+4&&standard<maxad-20){
          	   act_time=(2*maxad-setside);
       }
       if(standard<minad-4&&standard>minad-20){
          	   act_time=(2*minad-setside);
       }


}

