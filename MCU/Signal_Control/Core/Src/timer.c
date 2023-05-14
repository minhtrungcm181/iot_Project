/*
 * timer.c
 *
 *  Created on: Mar 30, 2023
 *      Author: Trand
 */
#include "timer.h"

int timer_counter[N_TIMERS];
int timer_flag[N_TIMERS];

int TIMER_CYCLE = 10;

void SW_TIM_Init(void)
{
	for (int i = 0; i < N_TIMERS; i++){
		setTimer(i, 10);
	}
}

void setTimer(int TIMx, int duration)
{
	timer_counter[TIMx] = duration / TIMER_CYCLE ;
	timer_flag[TIMx] = 0;
}

int get_flag(int TIMx)
{
	return timer_flag[TIMx];
}

void timer_run ()
{
	for (int i = 0; i < N_TIMERS; i++){
		if( timer_counter[i] > 0){
			timer_counter[i]--;
			if( timer_counter[i] == 0) timer_flag[i] = 1;
		}
	}
}
