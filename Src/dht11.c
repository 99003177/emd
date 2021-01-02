/*
 * dht11.c
 *
 *  Created on: Jan 1, 2021
 *      Author: sharath chandra
 */
#include "main.h"
#include <stdint.h>
#include "dht11.h"



void Set_Pin_Op (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Ip (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void DHT11_Strt (void)
{
	Set_Pin_Op (gpio_input_GPIO_Port, GPIO_PIN_1);
	HAL_GPIO_WritePin (gpio_input_GPIO_Port, GPIO_PIN_1, DISABLE);
	HAL_Delay(18000);
	HAL_GPIO_WritePin(gpio_input_GPIO_Port, GPIO_PIN_1, ENABLE);
	HAL_Delay(20);
	Set_Pin_Ip(gpio_input_GPIO_Port, GPIO_PIN_1);
}

uint8_t DHT11_Check_Resp (void)
{
	uint8_t Response = 0;
	HAL_Delay (40);
	if (!(HAL_GPIO_ReadPin (gpio_input_GPIO_Port,GPIO_PIN_1)))
	{
		HAL_Delay (80);
		if ((HAL_GPIO_ReadPin (gpio_input_GPIO_Port, GPIO_PIN_1)))
			Response = 1;
		else
			Response = -1;
	}
	while ((HAL_GPIO_ReadPin (gpio_input_GPIO_Port, GPIO_PIN_1)));
	return Response;
}

uint8_t DHT11_read (void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (gpio_input_GPIO_Port, GPIO_PIN_1)));
		HAL_Delay (40);
		if (!(HAL_GPIO_ReadPin (gpio_input_GPIO_Port, GPIO_PIN_1)))
		{
			i&= ~(1<<(7-j));
		}
		else
		{
			i|= (1<<(7-j));
		}
		while ((HAL_GPIO_ReadPin (gpio_input_GPIO_Port, GPIO_PIN_1)));
	}
	return i;
}

