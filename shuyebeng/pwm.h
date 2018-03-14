/*
 * pwm.h
 *
 *  Created on: 2015��8��2��
 *      Author: c
 */

#ifndef PWM_H_
#define PWM_H_

/*
 * ʹ�÷���Ϊ��
 * ����˳ʱ����ת���������ٶ�Ϊǧ����0~1000��
 * 		TB0_PWM_SetPermill()
 * 		������ǧ�ֱ�Ϊ0ʱ����ζ�Ŵ�ʱ�ٶ�Ϊ0��
 */

extern char TB0_PWM_SetPeriod(unsigned int Period);
extern char TB0_PWM_SetPermill(char Channel,unsigned int Duty);
extern void MotorPlus_ON(int duty1);					//when set dutyx = 0;it means turn off motor
extern void MotorNeg_ON(int duty2);					//




#endif /* PWM_H_ */

