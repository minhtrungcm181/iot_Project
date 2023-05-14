/*
 * input_reading.c
 *
 *  Created on: Mar 30, 2023
 *      Author: Trand
 */

#include "input_reading.h"

static GPIO_PinState buttonBuffer [N_BUTTONS];
// we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1 [ N_BUTTONS ];
static GPIO_PinState debounceButtonBuffer2 [ N_BUTTONS ];
// we define a flag for a button pressed more than 1 second .
static uint8_t flagForButtonPress1s [ N_BUTTONS ];
// we define counter for automatically increasing the value
// after the button is pressed more than 1 second .
static uint16_t counterForButtonPress1s [ N_BUTTONS ];

static GPIO_TypeDef* PORT[] = {GPIOC};
static uint16_t PIN[] = {GPIO_PIN_13};

void button_reading()
{
	for ( uint8_t i = 0; i < N_BUTTONS ; i ++){
		debounceButtonBuffer2 [i] = debounceButtonBuffer1 [i];
		debounceButtonBuffer1 [i] = HAL_GPIO_ReadPin (PORT[i], PIN[i]);
		if( debounceButtonBuffer1 [i] == debounceButtonBuffer2 [i])
			buttonBuffer [i] = debounceButtonBuffer1 [i];
		if( buttonBuffer [i] == IS_PRESSED ){
		// if a button is pressed , we start counting
			if( counterForButtonPress1s [i] < DURATION_FOR_AUTO_INCREASING ){
				counterForButtonPress1s [i ]++;
			}
			else {
				// the flag is turned on when 1 second has passed
				// since the button is pressed .
				flagForButtonPress1s [i] = 1;
			}
		}
		else {
			counterForButtonPress1s [i] = 0;
			flagForButtonPress1s [i] = 0;
		}
	}
}
uint8_t is_pressed ( uint8_t idx )
{
	assert_param(IS_IDX_BUTTON(idx));

	return ( buttonBuffer [idx] == IS_PRESSED );
}

uint8_t is_pressed_1s ( uint8_t idx )
{
	assert_param(IS_IDX_BUTTON(idx));

	return ( flagForButtonPress1s[idx] == 1);
}

