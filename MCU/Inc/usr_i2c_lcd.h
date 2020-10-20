/*
 * usr_i2c_lcd.h
 *
 *  Created on: Oct 8, 2020
 *      Author: Park
 */

#ifndef INC_USR_I2C_LCD_H_
#define INC_USR_I2C_LCD_H_

#define I2C_LCD_ADDRESS (0x27<<1)

void lcd_command(uint8_t command);
void lcd_data(uint8_t data);
void i2c_lcd_Init(void);
void lcd_string(char* str);
void lcd_move(uint8_t row, uint8_t col);
void lcd_clear(void);

#endif /* INC_USR_I2C_LCD_H_ */
