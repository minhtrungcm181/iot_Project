/*
 * delay_timer_dht.h
 *
 *  Created on: May 4, 2023
 *      Author: Trand
 */

#ifndef INC_DELAY_TIMER_DHT_H_
#define INC_DELAY_TIMER_DHT_H_

#include "main.h"
void DELAY_TIM_Init(TIM_HandleTypeDef *htim);
void DELAY_TIM_Us(TIM_HandleTypeDef *htim, uint16_t time);
void DELAY_TIM_Ms(TIM_HandleTypeDef *htim, uint16_t Time);

#endif /* INC_DELAY_TIMER_DHT_H_ */
