/*
 * pidctl.c
 *
 *  Created on: 2015年8月5日
 *      Author: c
 */

#include"MSP430X54X.h"
#include"lcddisplay.h"
#include"adtransfer.h"
#include"fourkey.h"
#include"pidctl.h"
    //定义变量
    int ii=0;
    int Kp=1;                       //PI调节的比例常数
    //float Ti;                       //PI调节的积分常数
    //float T;                        //采样周期
    int Ki=1;
    int ek=0;                 //偏差e[k]
    int ek1=0;                      //偏差e[k-1]
    int ek2=0;                      //偏差e[k-2]
    int uk=0;                       //u[k]
    int uk1=0;
    int adjust=0;
    int sk=0;
    int sk1=0;
    unsigned int ddisduty[]={500,452,403,370,336,297,264,215,164,110,64,25,0};   //设定占空比参数
            //调节器输出调整量
    unsigned char tspeed[]={0,30,35,40,45,50,55,60,65,70,75,80,85};
    unsigned char freq_bef=0;
    //变量初始化


    // Ki=KpT/Ti=0.8，微分系数Kd=KpTd/T=0.8,Td=0.0002,根据实验调得的结果确定这些参数



        int setsta;
        int average_bef=0;
        int num_bef;
        int tt=0;
void piadjust(void)  //PI调节算法
    {
         if(tt>0){
             tt=tt-1;
         }
         if(showspeed==0){
         showspeed=average-29;
         }
       if(num!=num_bef){
           num_bef=num;
           tt=400;
           ii=0;

         //  showspeed=setsta;
       }
       if(tt==0){
        sk=average;

       switch(num){
       case 1:setsta=set_average-28;break;       //30
       case 2:setsta=set_average-26;break;       //34
       case 3:setsta=set_average-23;break;       //40
       case 4:setsta=set_average-21;break;       //44
       case 5:setsta=set_average-18;break;      //50
       case 6:setsta=set_average-16;break;       //54
       case 7:setsta=set_average-13;break;       //60
       case 8:setsta=set_average-11;break;       //64
       case 9: setsta=set_average-8;break;       //70
       case 10:setsta=set_average-6 ;break;      //74
       case 11:setsta=set_average-3 ;break;      //80
       case 12:setsta=set_average   ;break;      //86
       default:break;
       }


       if(sk1==0){
           sk1=set_average-29;
       }
       ek=sk-setsta;
       ek1=sk1-setsta;

       if((ii<1000)&&(sk1-setsta<0)){
           ii=ii+1;
           if(setsta-sk1>20){
               sk1=sk1+(setsta-sk1)/2;
           }
           else{
           if (sk>setsta){
               sk1=sk1+(setsta-sk1)/3;
           }
           else{//(sk>setsta){
            sk1=sk1-(sk-setsta)/2;
           // uk=Kp*(ek1-ek)/3+Ki*ek/7;
            //    sk1=sk1+uk;
           }
           }
       }
                               if((ii<1000)&&(sk1>setsta)){
                                         ii=ii+1;
                                         if(sk1-setsta>20){
                                             sk1=sk1-(sk1-setsta)/3*2;


                                         }
                                         else{
                                      if(sk<setsta){
                                                      sk1=sk1+(setsta-sk1)/3;
                                        }
                                          else{
                                         sk1=sk1-(sk-setsta)/2;
             //  uk=Kp*(ek1-ek)/3+Ki*ek/7;
             //   sk1=sk1+uk;
                                               }

                                         }

                               }

             showspeed=sk1;
           if(set_average<sk1){
               pduty=0;
           }
           else{
           pduty=(set_average-sk1)*17;
           }
           if(ii==1000){
             showspeed=setsta;
             pduty=ddisduty[num];
           }

      }


     }
