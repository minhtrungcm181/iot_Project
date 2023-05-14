/*
 * DHT11.c
 *
 *  Created on: May 4, 2023
 *      Author: Trand
 */

#include "DHT11.h"
#include "delay_timer_dht.h"
#include "timer.h"

extern GPIO_TypeDef * LED_Port[];
extern uint16_t LED_Pin[];

DHT_Name sensor_DHT;

static void DHT_DelayInit(DHT_Name* DHT)
{
	DELAY_TIM_Init(DHT->Timer);
}
static void DHT_DelayUs(DHT_Name* DHT, uint16_t Time)
{
	DELAY_TIM_Us(DHT->Timer, Time);
}

static void DHT_DelayMs(DHT_Name* DHT, uint16_t Time)
{
	DELAY_TIM_Ms(DHT->Timer, Time);
}

static void DHT_SetPinOut(DHT_Name* DHT)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT->Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHT->PORT, &GPIO_InitStruct);
}
static void DHT_SetPinIn(DHT_Name* DHT)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT->Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(DHT->PORT, &GPIO_InitStruct);
}
static void DHT_WritePin(DHT_Name* DHT, uint8_t Value)
{
	HAL_GPIO_WritePin(DHT->PORT, DHT->Pin, Value);
}
static uint8_t DHT_ReadPin(DHT_Name* DHT)
{
	uint8_t Value;
	Value =  HAL_GPIO_ReadPin(DHT->PORT, DHT->Pin);
	return Value;
}
//********************************* Middle level Layer ****************************************************//
static uint8_t DHT_Start(DHT_Name* DHT)
{
	uint8_t Response = 0;
	DHT_SetPinOut(DHT);
	DHT_WritePin(DHT, RESET);
	DHT_DelayUs(DHT, DHT->Type);
	DHT_WritePin(DHT, SET);
	DHT_DelayUs(DHT, 30);
	DHT_SetPinIn(DHT);
	DHT_DelayUs(DHT, 40);
	if (!DHT_ReadPin(DHT))
	{
		DHT_DelayUs(DHT, 80);
		if(DHT_ReadPin(DHT))
		{
			Response = 1;
		}
		else Response = 0;
	}
	while(DHT_ReadPin(DHT));

	return Response;
}
static uint8_t DHT_Read(DHT_Name* DHT)
{
	uint8_t Value = 0;
	DHT_SetPinIn(DHT);
	for(int i = 0; i<8; i++)
	{
		while(!DHT_ReadPin(DHT));
		DHT_DelayUs(DHT, 40);
		if(!DHT_ReadPin(DHT))
		{
			Value &= ~(1<<(7-i));
		}
		else Value |= 1<<(7-i);
		while(DHT_ReadPin(DHT));
	}
	return Value;
}

//************************** High Level Layer ********************************************************//
void DHT_Init(DHT_Name* DHT, uint8_t DHT_Type, TIM_HandleTypeDef* Timer, GPIO_TypeDef* DH_PORT, uint16_t DH_Pin)
{
	if(DHT_Type == DHT11)
	{
		DHT->Type = DHT11_STARTTIME;
	}
	else if(DHT_Type == DHT22)
	{
		DHT->Type = DHT22_STARTTIME;
	}
	DHT->PORT = DH_PORT;
	DHT->Pin = DH_Pin;
	DHT->Timer = Timer;
	DHT->Status = 1;
	DHT_DelayInit(DHT);
}

void DHT_ReadTempHum()
{
	if (get_flag(2)){
		HAL_GPIO_TogglePin(LED_Port[1], LED_Pin[1]);
		setTimer(2, 1000);
	}
	DHT_Name* DHT = &sensor_DHT;
	uint8_t Temp1, Temp2, RH1, RH2;
	uint16_t Temp, Humi, SUM = 0;
	DHT_Start(DHT);
	RH1 = DHT_Read(DHT);
	RH2 = DHT_Read(DHT);
	Temp1 = DHT_Read(DHT);
	Temp2 = DHT_Read(DHT);
	SUM = DHT_Read(DHT);
	Temp = (Temp1<<8)|Temp2;
	Humi = (RH1<<8)|RH2;
	DHT->Status = SUM;
	//DHT->Temp = (float)(Temp/10.0);
	//DHT->Humi = (float)(Humi/10.0);
	DHT->Temp = Temp;
	DHT->Humi = Humi;
	//return SUM;
}
