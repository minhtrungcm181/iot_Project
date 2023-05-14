/*
 * DHT.h
 *
 *  Created on: May 3, 2023
 *      Author: Trand
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_
#include "main.h"
uint8_t DHT_ready();
void request_DHT();
uint8_t record_data_DHT(uint8_t);
uint8_t* get_data_DHT();

#endif /* INC_DHT_H_ */
