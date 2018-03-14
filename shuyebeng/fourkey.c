/*
 * fourkey.c
 *
 *  Created on: 2015年8月3日
 *      Author: c
 */


/*
 * fourkey.c
 *
 *  Created on: 2015年8月2日
 *      Author: c
 */
#include<msp430f5438a.h>
#include"fourkey.h"

void P1_IODect();
void P16_Onclick();
void P17_Onclick();

void GPIO_int()
{
	P11DIR&=~BIT1;
	P11DIR&=~BIT2;
	P1DIR&=~BIT6;
	P1IES|=BIT6;
	P1IE|=BIT6;
	P1DIR&=~BIT7;
	P1IES|=BIT7;
	P1IE|=BIT7;
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
	P1_IODect();
	P1IFG=0;
}

void P1_IODect()
{
	unsigned int Push_Key=0;
	Push_Key=P1IFG&(~P1DIR);
	_delay_cycles(200000);
	if((P1IN&Push_Key)==0)
	{
		switch(Push_Key){
		case BIT6: P16_Onclick(); break;
		case BIT7: P17_Onclick(); break;
		default:  break;
		}
	}
}

void P16_Onclick()
{
	if(num<12){

	num=num+1;
	}
	else{
		num=12;
	}
}

void P17_Onclick()
{
	if(num==0){
	num=0;
	}
	else{
		num=num-1;
	}

}


