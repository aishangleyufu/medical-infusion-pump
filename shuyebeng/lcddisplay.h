/*
 * lcddisplay.h
 *
 *  Created on: 2015��7��29��
 *      Author: c
 */

#ifndef LCDDISPLAY_H_
#define LCDDISPLAY_H_
#define uchar unsigned char
extern void busy_lcd(void);
extern void wr_lcd(uchar DATA,uchar flog);
extern void lcd_Init(void);
extern void clc_lcd(void);
extern void gotoxy(unsigned char y, unsigned char x);
extern void showstr(uchar *str);
extern void displayspeed(void);
extern unsigned int average;
extern unsigned int act_time;
extern unsigned int set_average;
extern unsigned int showspeed;
#endif /* LCDDISPLAY_H_ */

