/*
 * pidctl.h
 *
 *  Created on: 2015��8��5��
 *      Author: c
 */

#ifndef PIDCTL_H_
#define PIDCTL_H_

extern void piadjust(void);
extern unsigned char num;
extern unsigned int average;
extern unsigned int set_average;
extern unsigned int showspeed;

extern unsigned int pduty;
#endif /* PIDCTL_H_ */