/*
 * usr_i2c_lcd.c
 *
 *  Created on: Oct 8, 2020
 *      Author: park
 */

#include "main.h"
#include "usr_i2c_lcd.h"

extern I2C_HandleTypeDef hi2c1;

void lcd_command(uint8_t command)
{
	uint8_t high_nibble, low_nibble;
	uint8_t i2c_buffer[4];
	high_nibble = command & 0xf0;
	low_nibble = (command<<4) & 0xf0;
	i2c_buffer[0] = high_nibble | 0x04 |0x08;  //en =1, rs=0, rw =0 backlight = 1
	i2c_buffer[1] = high_nibble | 0x00 |0x08;  //en =0, rs=0, rw =0
	i2c_buffer[2] = low_nibble | 0x04 |0x08;   //en =1, rs=0, rw =0
	i2c_buffer[3] = low_nibble | 0x00 |0x08;   //en =0, rs=0, rw =0

	while(HAL_I2C_Master_Transmit(&hi2c1, I2C_LCD_ADDRESS, i2c_buffer, 4, 100) != HAL_OK)
	{
		/* none */
	}

	return;
}

void lcd_data(uint8_t data)
{
	uint8_t high_nibble, low_nibble;
	uint8_t i2c_buffer[4];
	high_nibble = data & 0xf0;
	low_nibble = (data<<4) & 0xf0;
	i2c_buffer[0] = high_nibble | 0x05 |0x08;  //en =1, rs=0, rw =0 backlight = 1
	i2c_buffer[1] = high_nibble | 0x01 |0x08;  //en =0, rs=0, rw =0
	i2c_buffer[2] = low_nibble | 0x05 |0x08;   //en =1, rs=0, rw =0
	i2c_buffer[3] = low_nibble | 0x01 |0x08;   //en =0, rs=0, rw =0

	while(HAL_I2C_Master_Transmit(&hi2c1, I2C_LCD_ADDRESS, i2c_buffer, 4, 100) != HAL_OK)
	{
		/* none */
	}

	return;
}

void i2c_lcd_Init(void)
{
	lcd_command(0x33);
	lcd_command(0x32);
	lcd_command(0x28);		// Function  set 4-bit mode
	lcd_command(0x0c);		// Display ON/Off
	lcd_command(0x06);		// Entry mode set
	lcd_command(0x01);		// Clear Displayer
	HAL_Delay(200);
}

void lcd_string(char* str)
{
	while(*str)
		lcd_data(*str++);

	return;
}

void lcd_move(uint8_t row, uint8_t col)
{
	lcd_command(0x80 | row<<6 | col);

	return;
}

void lcd_clear(void)
{
	lcd_command(0x01);
	HAL_Delay(2);
	lcd_command(0x02);

	return;
}
