/*
 * usr_dht11.h
 *
 *  Created on: Oct 8, 2020
 *      Author: Park
 */

#ifndef INC_USR_DHT11_H_
#define INC_USR_DHT11_H_

#define DHT11_PORT GPIOE
#define DHT11_PIN GPIO_PIN_0

void _delay_us(uint32_t us);
void DHT11_Init(void);
void DHT11_Trigger(void);
void DHT11_setInput(void);
void DHT11_setOutput(void);
void DHT11_ReadData(void);
uint8_t DHT11_Parse(void);


#endif /* INC_USR_DHT11_H_ */
