/*
 * keyscan.c
 *
 *  Created on: 2015年8月3日
 *      Author: c
 */



#include <msp430.h>
#include<msp430f5438a.h>
int key_scan()
{
	//WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer

   	int h=0;
    int l=0;
    int keycode;  //define 5 variable we need : keyode、h、l

   	P2DIR|=BIT7+BIT6+BIT5+BIT4;
    P2OUT|=BIT7+BIT6+BIT5+BIT4;         //L1~L4 set 1

    P7DIR|=BIT7+BIT6+BIT5+BIT4;
    P7OUT&=~(BIT7+BIT6+BIT5+BIT4);      //H1~H4 SET 0,

    P2DIR&=~(BIT7+BIT6+BIT5+BIT4);         //P2.4~P2.7 SET AS INPUT;
    if((P2IN&0xf0)!=0xf0)
    {
         _delay_cycles(200000);
         if((P2IN&0xf0)!=0xf0)
         {
         switch(P2IN&0xf0)                //获得列值 get the column
         {
              case 0x70:l=3;break;
              case 0xb0:l=2;break;
              case 0xd0:l=1;break;
              case 0xe0:l=0;break;
         }
         P2DIR|=BIT7+BIT6+BIT5+BIT4;
         P2OUT&=~(BIT7+BIT6+BIT5+BIT4);  //L1~L4 set 0

         P7DIR|=BIT7+BIT6+BIT5+BIT4;
         P7OUT|=BIT7+BIT6+BIT5+BIT4;     //H1~H4 SET 1,

         P7DIR&=~(BIT7+BIT6+BIT5+BIT4);      //P7.4~P7.7 SET AS INPUT;
         switch(P7IN&0xf0)                //获得行值 get the row
         {
	         case 0x70:h=0;break;
	         case 0xb0:h=1;break;
	         case 0xd0:h=2;break;
	         case 0xe0:h=3;break;
	     }
         keycode=h*4+l+1;                         //由行值和列值得到键值:1~16 get the keycode through row and column
	    // n=n+1;                         //对检测到该键被连续按下的次数进行计数 count the time
     }
	 else
	 {                                  //无键按下，将行，列，计数清零 no click,clear the variable of row and column
	     keycode=0;

	 }
    }
	// keycode=h*4+l+1;                         //由行值和列值得到键值:1~16 get the keycode through row and column
	 if(keycode!=0)
	 {                                   //当连续第100次检测到某一个键时，此按键有效 the keycode is  valid when the key counted for 100times
	  return keycode;
	 }
	 else

	 return 0;

}
