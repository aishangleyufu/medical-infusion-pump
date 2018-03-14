/*
 * clock.h
 *
 *  Created on: 2015Äê8ÔÂ2ÈÕ
 *      Author: c
 */

#ifndef CLOCK_H_
#define CLOCK_H_
extern unsigned char second;
extern unsigned char min;
extern unsigned char hour;
extern void TIMERA0main(void);
extern unsigned char T_2ms;
extern unsigned char freq;
extern unsigned int pduty;
extern unsigned char num;
extern volatile int ADC_Result;
extern float Voltage_ch1;
extern int code;
extern unsigned int mode;
extern unsigned int average;
#endif /* CLOCK_H_ */
