/*
 * DHT11.h
 *
 *  Created on: May 4, 2023
 *      Author: Trand
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "main.h"
#define DHT11_STARTTIME 20000
#define DHT22_STARTTIME 12000
#define DHT11 0x01
#define DHT22 0x02
typedef struct
{
	uint16_t Type;
	TIM_HandleTypeDef* Timer;
	uint16_t Pin;
	GPIO_TypeDef* PORT;
	uint8_t Status;
	int Temp;
	int Humi;
}DHT_Name;

void DHT_Init(DHT_Name* DHT, uint8_t DHT_Type, TIM_HandleTypeDef* Timer, GPIO_TypeDef* DH_PORT, uint16_t DH_Pin);
void DHT_ReadTempHum();

#endif /* INC_DHT11_H_ */
