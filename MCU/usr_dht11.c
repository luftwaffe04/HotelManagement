/*
 * usr_dht11.c
 *
 *  Created on: Oct 7, 2020
 *      Author: park
 *	DHT11은 데이터시트를 보면 특정 신호값을 특정 주기에 맞춰서 주면 데이터를 날려보낸다
 */
#include "main.h"
#include "usr_dht11.h"

void _delay_us(uint32_t us)
{
	// 16Mhz 시스템에서 작동하는 delay_us 함수
	if(us > 1) {
		volatile uint32_t count = us*6 -4;
		while(count--);
	}
	else {
		volatile uint32_t count = 4;
		while(count--);
	}

	return;
}

void DHT11_Init(void)
{
	// Initialize Signal
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
	HAL_Delay(3000);

	return;
}

void DHT11_Trigger(void)
{
	// Start Signal
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
	_delay_us(7);

	return;
}

void DHT11_setInput(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = DHT11_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // Change Out to In
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

	return;
}

void DHT11_setOutput(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = DHT11_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; //Change Input to Output
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

	return;
}

void DHT11_ReadData(void)
{
	while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 1); // until low
	while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 0); // until high
	while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 1); // until low -> next is data

	return;
}

uint8_t DHT11_Parse(void)
{
	uint8_t parse_data = 0;

	for(int i = 0; i < 8; i++)
	{
		//when Input Data == 0
		while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 0);
		_delay_us(16);
		parse_data <<= 1;

		//when Input Data == 1
		if(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
		{
			parse_data |= 1;
		}
		while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 1);
	}

	return parse_data;
}
