/*
 * pwm.h
 *
 *  Created on: 2015年8月2日
 *      Author: c
 */

#ifndef PWM_H_
#define PWM_H_

/*
 * 使用范例为：
 * 启动顺时针电机转动，输入速度为千分率0~1000；
 * 		TB0_PWM_SetPermill()
 * 		当输入千分比为0时，意味着此时速度为0；
 */

extern char TB0_PWM_SetPeriod(unsigned int Period);
extern char TB0_PWM_SetPermill(char Channel,unsigned int Duty);
extern void MotorPlus_ON(int duty1);					//when set dutyx = 0;it means turn off motor
extern void MotorNeg_ON(int duty2);					//




#endif /* PWM_H_ */

