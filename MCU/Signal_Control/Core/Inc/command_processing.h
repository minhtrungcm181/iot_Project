/*
 * command_processing.h
 *
 *  Created on: Apr 6, 2023
 *      Author: Trand
 */

#ifndef INC_COMMAND_PROCESSING_H_
#define INC_COMMAND_PROCESSING_H_
#include "main.h"
uint8_t request_ready();
uint8_t record(uint8_t);
uint8_t* get_request();
void request_processing();

#endif /* INC_COMMAND_PROCESSING_H_ */
