/*
 * timer.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Trand
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define N_TIMERS	3

void SW_TIM_Init(void);

void setTimer(int, int);

void timer_run();

int get_flag(int);

#endif /* INC_TIMER_H_ */
